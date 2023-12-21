#include "UQuest.h"

#include "FQuestDataTypes.h"
#include "UQuestSubsystem.h"

void UQuest::Setup(const FDataTableRowHandle& QuestRow, UQuestSubsystem* QuestSS)
{
	QuestSubsystem = QuestSS;
	
	QuestHandle = QuestRow;
	QuestDetails = *QuestHandle.GetRow<FQuestDetails>(FString(""));
	CurrentStage = 0;
	IsQuestComplete = false;

	SetupStage();
}

void UQuest::AddObjectiveProgression(const FDataTableRowHandle& ObjectiveRow, const int32 Count)
{
	const int32* Progress = CurrentObjectiveProgress.Find(ObjectiveRow.RowName);
	// TODO if persistent, then add to completed objectives
	
	if (!Progress) return;

	const FQuestObjective* Objective = ObjectiveRow.GetRow<FQuestObjective>(FString(""));
	if (*Progress >= Objective->Quantity) return;
	
	const int32 NewProgress = *Progress + Count;
	CurrentObjectiveProgress.Add(ObjectiveRow.RowName, NewProgress);
	
	if (NewProgress >= Objective->Quantity)
	{
		OnObjectiveUpdated.Broadcast(ObjectiveRow, true);
		if (IsStageComplete(QuestDetails.Stages[CurrentStage]))
		{
			if (CurrentStage >= QuestDetails.Stages.Num() - 1)
			{
				IsQuestComplete = true;
			}
			if (IsQuestComplete)
			{
				OnQuestCompleted.Broadcast(QuestHandle);
			}
			else
			{
				CurrentStage++;
				SetupStage();
				OnStageCompleted.Broadcast(QuestDetails.Stages[CurrentStage - 1]);
			}
		}
	}
	else
	{
		OnObjectiveUpdated.Broadcast(ObjectiveRow, false);	
	}
}

void UQuest::SetupStage()
{
	CurrentObjectiveProgress.Empty();

	const TMap<FName, int32>* ObjectiveProgress = nullptr;
	if (QuestSubsystem != nullptr)
	{
		ObjectiveProgress = &QuestSubsystem->QuestLog->ObjectiveProgress;
	}
	
	for (FDataTableRowHandle ObjectiveRow : QuestDetails.Stages[CurrentStage].Objectives)
	{
		if (ObjectiveProgress != nullptr && ObjectiveProgress->Contains(ObjectiveRow.RowName))
		{
			CurrentObjectiveProgress.Add(ObjectiveRow.RowName, *ObjectiveProgress->Find(ObjectiveRow.RowName));
		}
		else
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
