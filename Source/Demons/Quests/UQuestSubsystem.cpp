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
	DebugLog("Adding quest log component")
	QuestLog = Cast<UQuestLog>(QuestSystem->GetComponentByClass(UQuestLog::StaticClass()));
}

void UQuestSubsystem::AddQuest(FDataTableRowHandle QuestRow)
{
	if (QuestLog == nullptr)
	{
		DebugLog("Quest Log is not set, cannot add quest!");
		return;
	}
	
	if (QuestRow.IsNull() || QuestRow.RowName == NAME_None)
	{
		DebugLog("Tried to add quest, but quest was null!");
		return;
	}

	if (QuestLog->ActiveQuestRefs.Contains(QuestRow))
	{
		return;
	}

	QuestLog->AddQuest(QuestRow);
}
