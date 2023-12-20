#include "UInteractionComponent.h"

#include "FInteractionsDataTypes.h"
#include "Demons/Debug/DebugUtil.h"

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

FInteractionDetails* UInteractionComponent::DetermineInteraction() const
{
	if (InteractionTable == nullptr || CurrentInteraction.IsNone()) return nullptr;
	
	FInteractionDetails* Interaction = InteractionTable->FindRow<FInteractionDetails>(CurrentInteraction, FString(""));
	if (Interaction == nullptr)
	{
		DebugLogError("Invalid Interaction row: " + CurrentInteraction.ToString())
		return nullptr;
	}

	// TODO loop through transitions, check CanSkip, Assign quest progress if persistent, etc
	
	return Interaction;
}
