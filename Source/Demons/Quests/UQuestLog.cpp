#include "UQuestLog.h"

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

void UQuestLog::AddQuestToLog(const FDataTableRowHandle& QuestRow)
{
	ActiveQuestRefs.Add(QuestRow);
}
