#include "FQuest.h"

#include "FQuestDataTypes.h"
#include "UQuestSubsystem.h"
#include "Demons/Debug/DebugUtil.h"

void UQuest::Setup(const FDataTableRowHandle& QuestRow)
{
	QuestID = QuestRow;
	QuestDetails = *QuestRow.GetRow<FQuestDetails>(FString(""));
	CurrentStage = 0;
	IsQuestComplete = false;

	SetupStage();
}

void UQuest::UpdateObjective(const FDataTableRowHandle& ObjectiveRow, const int32 Count)
{
	const int32* Progress = CurrentObjectiveProgress.Find(ObjectiveRow.RowName);
	if (!Progress) return;

	const FQuestObjective* Objective = ObjectiveRow.GetRow<FQuestObjective>(FString(""));
	if (*Progress >= Objective->Quantity) return;
	
	const int32 NewProgress = *Progress + Count;
	CurrentObjectiveProgress.Add(ObjectiveRow.RowName, NewProgress);
	
	if (NewProgress >= Objective->Quantity)
	{
		HandleCompletedObjective(ObjectiveRow);
	}
	
	OnQuestUpdated.Broadcast();
}

void UQuest::HandleCompletedObjective(const FDataTableRowHandle& ObjectiveRow)
{
	bool IsPersistent = ObjectiveRow.GetRow<FQuestObjective>(FString(""))->IsPersistent;
	if (IsPersistent)
	{
		OnObjectiveComplete.Broadcast(ObjectiveRow);
	}
	
	if (IsStageComplete(QuestDetails.Stages[CurrentStage]))
	{
		DebugLog("Stage complete!");
		CurrentStage++;
		if (CurrentStage >= QuestDetails.Stages.Num())
		{
			DebugLog("Quest complete: " + QuestDetails.QuestName.ToString());
			IsQuestComplete = true;
		}
		else
		{
			SetupStage();
		}
	}
}

void UQuest::SetupStage()
{
	CurrentObjectiveProgress.Empty();

	//const UQuestSubsystem* QuestSubsystem = GetWorld()->GetSubsystem<UQuestSubsystem>();
	//const TArray<FName> CompletedObjectives = QuestSubsystem->QuestLog->CompletedObjectives;
	
	for (FDataTableRowHandle ObjectiveRow : QuestDetails.Stages[CurrentStage].Objectives)
	{
		// if (CompletedObjectives.Contains(ObjectiveRow.RowName))
		// {
		// 	const FQuestObjective* Objective = ObjectiveRow.GetRow<FQuestObjective>(FString(""));
		// 	CurrentObjectiveProgress.Add(ObjectiveRow.RowName, Objective->Quantity);
		// }
		// else
		{
			CurrentObjectiveProgress.Add(ObjectiveRow.RowName, 0);	
		}
	}
}

bool UQuest::IsStageComplete(FQuestStage StageDetails) const
{
	for (const auto ObjectiveRow : StageDetails.Objectives)
	{
		if (!IsObjectiveComplete(ObjectiveRow))
		{
			return false;
		}
	}
	return true;
}

bool UQuest::IsObjectiveComplete(const FDataTableRowHandle& ObjectiveRow) const
{
	const int32 Progress = CurrentObjectiveProgress.FindRef(ObjectiveRow.RowName);
	const int32 Quantity = ObjectiveRow.GetRow<FQuestObjective>(FString(""))->Quantity;
	return Progress >= Quantity;
}

