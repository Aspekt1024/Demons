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
	
	UFUNCTION(BlueprintImplementableEvent, Category="Quests")
	void AddQuest(FDataTableRowHandle QuestRow);

	UFUNCTION(BlueprintCallable)
	bool HasQuest(const FDataTableRowHandle& QuestRow);

private:
	void AddQuestToLog(const FDataTableRowHandle& QuestRow);
};
