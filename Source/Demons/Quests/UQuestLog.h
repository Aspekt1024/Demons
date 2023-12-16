#pragma once

#include "CoreMinimal.h"
#include "UQuestLog.generated.h"

UCLASS(BlueprintType, Blueprintable)
class DEMONS_API UQuestLog : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	TArray<FDataTableRowHandle> ActiveQuestRefs;

	UPROPERTY(BlueprintReadOnly)
	TArray<FName> CompletedQuests;

	UPROPERTY(BlueprintReadOnly)
	TArray<FName> CompletedObjectives;

	UFUNCTION(BlueprintImplementableEvent)
	void OnQuestAdded(const FDataTableRowHandle& QuestRow);
	
	bool AddQuest(const FDataTableRowHandle& QuestRow);
	
private:
	bool HasQuest(const FDataTableRowHandle& QuestRow);
};
