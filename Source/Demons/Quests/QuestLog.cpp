#include "QuestLog.h"

#include "Quest.h"
#include "Demons/Debug/DebugUtil.h"

void UQuestLog::AddQuest(const FDataTableRowHandle& QuestRow)
{
	if (HasQuest(QuestRow))
	{
		DebugLog("Already on quest " + QuestRow.RowName.ToString());
		return;
	}

	UQuest* Quest = NewObject<UQuest>();
	UQuestSubsystem* QuestSubsystem = GetQuestSubsystem();
	Quest->Setup(QuestRow, QuestSubsystem);
	Quests.Add(Quest);

	Quest->OnQuestCompleted.AddDynamic(this, &UQuestLog::OnQuestCompleted);
	
	OnQuestAdded.Broadcast(Quest);
}

void UQuestLog::AddObjectiveProgression(const FDataTableRowHandle& ObjectiveRow, int32 Count)
{
	const FQuestObjective* Objective = ObjectiveRow.GetRow<FQuestObjective>(FString(""));
	if (Objective == nullptr)
	{
		DebugLogError("failed to find objective " + ObjectiveRow.RowName.ToString())
		return;
	}
	
	if (Objective->IsPersistent)
	{
		if (ObjectiveProgress.Contains(ObjectiveRow.RowName))
		{
			Count += ObjectiveProgress[ObjectiveRow.RowName];
		}
		ObjectiveProgress.Add(ObjectiveRow.RowName, Count);
	}
	
	for (int i = Quests.Num() - 1; i >= 0; --i)
	{
		Quests[i]->AddObjectiveProgression(ObjectiveRow, Count);
	}
}

bool UQuestLog::HasQuest(const FDataTableRowHandle& QuestRow)
{
	for (const auto Quest : Quests)
	{
		if (Quest->QuestHandle.DataTable != QuestRow.DataTable) continue;
		if (Quest->QuestHandle.RowName != QuestRow.RowName) continue;
		return true;
	}
	
	return false;
}

void UQuestLog::OnQuestCompleted(const FDataTableRowHandle& QuestRow)
{
	UQuest* Quest = GetQuestFromRow(QuestRow);
	Quests.Remove(Quest);
}

UQuest* UQuestLog::GetQuestFromRow(const FDataTableRowHandle& QuestRow)
{
	for (UQuest* Quest : Quests)
	{
		if (Quest->QuestHandle.DataTable != QuestRow.DataTable) continue;
		if (Quest->QuestHandle.RowName != QuestRow.RowName) continue;
		return Quest;
	}

	return nullptr;
}

UQuestSubsystem* UQuestLog::GetQuestSubsystem() const
{
	const UWorld* World = GetWorld();
	if (!World)
	{
		DebugLogError("World was null :(");
		return nullptr;
	}
	
	const UGameInstance* GameInstance = World->GetGameInstance();
	if (!GameInstance)
	{
		DebugLogError("GameInstance was null :(");
		return nullptr;
	}

	UQuestSubsystem* QuestSubsystem = GameInstance->GetSubsystem<UQuestSubsystem>();
	if (!QuestSubsystem)
	{
		DebugLogError("QuestSubsystem was null :(");
	}
	return QuestSubsystem;
}
