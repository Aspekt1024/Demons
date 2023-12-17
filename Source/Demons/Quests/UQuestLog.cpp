#include "UQuestLog.h"

#include "FQuest.h"
#include "Demons/Debug/DebugUtil.h"

void UQuestLog::AddQuest(const FDataTableRowHandle& QuestRow)
{
	if (HasQuest(QuestRow))
	{
		DebugLog("Already on quest " + QuestRow.RowName.ToString());
		return;
	}

	UQuest* Quest = NewObject<UQuest>();
	Quest->Setup(QuestRow);
	Quests.Add(Quest);

	Quest->OnObjectiveComplete.AddUObject(this, &UQuestLog::HandleCompletedObjective);
	
	OnQuestAdded.Broadcast(Quest);
}

void UQuestLog::HandleCompletedObjective(const FDataTableRowHandle& ObjectiveRow)
{
	const FQuestObjective* Objective = ObjectiveRow.GetRow<FQuestObjective>(FString(""));
	if (Objective->IsPersistent)
	{
		CompletedObjectives.Add(ObjectiveRow.RowName);	
	}
}

void UQuestLog::UpdateObjective(const FDataTableRowHandle& ObjectiveRow, int32 Count)
{
	for (UQuest* Quest : Quests)
	{
		Quest->UpdateObjective(ObjectiveRow, Count);
		if (Quest->IsQuestComplete)
		{
			// TODO unbind from quest completion activities
			// TODO destroy the quest object, add to completed quests list
			DebugLog("Quest complete: " + Quest->QuestID.RowName.ToString());
		}
	}
}

bool UQuestLog::HasQuest(const FDataTableRowHandle& QuestRow)
{
	for (const auto Quest : Quests)
	{
		if (Quest->QuestID.DataTable != QuestRow.DataTable) continue;
		if (Quest->QuestID.RowName != QuestRow.RowName) continue;
		return true;
	}
	
	return false;
}