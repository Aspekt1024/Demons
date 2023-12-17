#pragma once

#include "CoreMinimal.h"
#include "UQuestLog.generated.h"

class UQuest;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FQuestAddDelegate, UQuest*, QuestRow);

UCLASS(BlueprintType, Blueprintable)
class DEMONS_API UQuestLog : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	TArray<FName> CompletedQuests;

	UPROPERTY(BlueprintReadOnly)
	TArray<FName> CompletedObjectives;

	UPROPERTY(BlueprintAssignable)
	FQuestAddDelegate OnQuestAdded;
	
	void AddQuest(const FDataTableRowHandle& QuestRow);
	void UpdateObjective(const FDataTableRowHandle& ObjectiveRow, int32 Count);
	
private:
	TArray<UQuest*> Quests;
	bool HasQuest(const FDataTableRowHandle& QuestRow);

	void HandleCompletedObjective(const FDataTableRowHandle& ObjectiveRow);
};
