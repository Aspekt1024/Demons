#include "UQuestLog.h"

#include "Demons/Debug/DebugUtil.h"

bool UQuestLog::AddQuest(const FDataTableRowHandle& QuestRow)
{
	if (HasQuest(QuestRow))
	{
		DebugLog("Already on quest " + QuestRow.RowName.ToString());
		return false;
	}

	ActiveQuestRefs.Add(QuestRow);
	return true;
}

bool UQuestLog::HasQuest(const FDataTableRowHandle& QuestRow)
{
	for (auto questRef : ActiveQuestRefs)
	{
		if (questRef.DataTable != QuestRow.DataTable) continue;
		if (questRef.RowName != QuestRow.RowName) continue;
		return true;
	}
	
	return false;
}