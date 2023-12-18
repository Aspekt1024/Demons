﻿#include "UQuestLog.h"

#include "UQuest.h"
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

	Quest->OnObjectiveUpdated.AddDynamic(this, &UQuestLog::OnObjectiveCompleted);
	Quest->OnQuestCompleted.AddDynamic(this, &UQuestLog::OnQuestCompleted);
	
	OnQuestAdded.Broadcast(Quest);
}

void UQuestLog::AddObjectiveProgression(const FDataTableRowHandle& ObjectiveRow, int32 Count)
{
	for (UQuest* Quest : Quests)
	{
		Quest->AddObjectiveProgression(ObjectiveRow, Count);
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
	// TODO unbind from quest completion activities
	// TODO destroy the quest object, add to completed quests list
	const UQuest* Quest = GetQuestFromRow(QuestRow);
	DebugLog("[QuestLog] Quest complete: " + Quest->QuestHandle.RowName.ToString());
}

void UQuestLog::OnObjectiveCompleted(const FDataTableRowHandle& ObjectiveRow, bool IsObjectiveComplete)
{
	const bool IsPersistent = ObjectiveRow.GetRow<FQuestObjective>(FString(""))->IsPersistent;
	if (IsPersistent)
	{
		CompletedObjectives.Add(ObjectiveRow.RowName);
	}
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
