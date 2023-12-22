#include "UInteractionComponent.h"

#include "FInteractionsDataTypes.h"
#include "Demons/Debug/DebugUtil.h"
#include "Demons/Quests/FQuestDataTypes.h"

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	CanInteract = true;
	
	QuestSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UQuestSubsystem>();
	if (QuestSubsystem == nullptr)
	{
		DebugLogError("Quest Subsystem has not been initialised")
	}

	if (InteractionTable != nullptr)
	{
		const TArray<FName> RowNames = InteractionTable->GetRowNames();
		if (RowNames.Num() > 0)
		{
			CurrentInteraction = RowNames[0];	
		}
	}
}

void UInteractionComponent::Interact()
{
	if (!CanInteract) return;
	
	OnInteract();
	QuestSubsystem->AddObjectiveProgression(CompletesObjective, 1);
	
	const FInteractionDetails* InteractionDetails = DetermineInteraction();
	if (InteractionDetails != nullptr)
	{
		OnInteractionDetermined(*InteractionDetails);	
	}
}

void UInteractionComponent::SetNonInteractable()
{
	CanInteract = false;
}

void UInteractionComponent::CompleteInteraction(FName InteractionName, bool AllowTransition)
{
	if (InteractionName == NAME_None)
	{
		DebugLogError("CompleteInteraction called with empty interaction name!")
		return;
	}
	
	if (ActionedInteractions.Contains(InteractionName)) return;

	ActionedInteractions.Add(InteractionName);
	
	FInteractionDetails* Interaction = InteractionTable->FindRow<FInteractionDetails>(InteractionName, FString(""));
	if (Interaction->QuestObjective.DataTable != nullptr && !Interaction->QuestObjective.RowName.IsNone())
	{
		const FQuestObjective* Objective = Interaction->QuestObjective.GetRow<FQuestObjective>(FString(""));
		QuestSubsystem->AddObjectiveProgression(Interaction->QuestObjective, Objective->Quantity);
	}

	if (Interaction->GiveQuest.DataTable != nullptr && !Interaction->GiveQuest.RowName.IsNone())
	{
		QuestSubsystem->AddQuest(Interaction->GiveQuest);
	}

	if (AllowTransition)
	{
		const FName NextInteraction = GetValidInteractionFromTransitions(Interaction);
		if (NextInteraction != NAME_None)
		{
			CurrentInteraction = NextInteraction;
		}	
	}
}

FInteractionDetails* UInteractionComponent::DetermineInteraction()
{
	if (InteractionTable == nullptr || CurrentInteraction.IsNone()) return nullptr;

	FInteractionDetails* Interaction = InteractionTable->FindRow<FInteractionDetails>(CurrentInteraction, FString(""));
	if (Interaction == nullptr)
	{
		DebugLogError("Invalid Interaction row: " + CurrentInteraction.ToString())
		return nullptr;
	}
	
	while (TryProgressInteraction(Interaction))
	{
		Interaction = InteractionTable->FindRow<FInteractionDetails>(CurrentInteraction, FString(""));
	}
	
	return Interaction;
}

bool UInteractionComponent::TryProgressInteraction(FInteractionDetails* Interaction)
{
	const FName InteractionName = GetValidInteractionFromTransitions(Interaction);
	if (InteractionName != NAME_None)
	{
		CompleteInteraction(CurrentInteraction, false);
		CurrentInteraction = InteractionName;
		return true;
	}

	return false;
}

FName UInteractionComponent::GetValidInteractionFromTransitions(FInteractionDetails* Interaction) const 
{
	for (const FInteractionTransition& Transition : Interaction->TransitionDetails)
	{
		if (CanTransition(Transition))
		{
			return Transition.Interaction.RowName;
		}
	}
	return NAME_None;
}

bool UInteractionComponent::CanTransition(const FInteractionTransition& InteractionTransition) const
{
	if (InteractionTransition.Interaction.DataTable == nullptr || InteractionTransition.Interaction.RowName.IsNone())
	{
		return false;
	}

	if (InteractionTransition.Interaction.DataTable != InteractionTable)
	{
		DebugLogError("Transition Data Table does not match Interaction component's InteractionTable type. This is not allowed!")
		return false;
	}

	if (!InteractionTransition.AllowsSkip && !ActionedInteractions.Contains(CurrentInteraction))
	{
		return false;
	}
	
	for (FDataTableRowHandle Objective : InteractionTransition.RequiredObjectives)
	{
		if (!QuestSubsystem->IsObjectiveComplete(Objective))
		{
			return false;
		}
	}
	return true;
}