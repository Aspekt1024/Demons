#include "UQuestSubsystem.h"

#include "AQuestSystem.h"
#include "Demons/Debug/DebugUtil.h"

AQuestSystem* QuestSystem;

void UQuestSubsystem::RegisterQuestSystem(AQuestSystem* System)
{
	QuestSystem = System;
	if (QuestSystem == nullptr)
	{
		DebugLog("Failed to find Quest system");
		return;
	}
	QuestLog = Cast<UQuestLog>(QuestSystem->GetComponentByClass(UQuestLog::StaticClass()));
}

void UQuestSubsystem::AddQuest(FDataTableRowHandle QuestRow)
{
	if (QuestLog == nullptr)
	{
		DebugLogError("Quest Log is not set, cannot add quest!");
		return;
	}
	
	if (QuestRow.IsNull() || QuestRow.RowName == NAME_None)
	{
		DebugLogError("Tried to add quest, but quest was null!");
		return;
	}

	QuestLog->AddQuest(QuestRow);
}

void UQuestSubsystem::UpdateObjective(const FDataTableRowHandle& ObjectiveRow, int32 Count)
{
	QuestLog->UpdateObjective(ObjectiveRow, Count);
	OnQuestUpdated.Broadcast();
}
