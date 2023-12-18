#pragma once

#include "CoreMinimal.h"
#include "UQuestLog.generated.h"

class UQuestSubsystem;
class UQuest;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FQuestAddDelegate, UQuest*, QuestRow);

UCLASS(BlueprintType, Blueprintable)
class DEMONS_API UQuestLog : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category="Quest")
	TArray<FName> CompletedQuests;

	UPROPERTY(BlueprintReadOnly, Category="Quest")
	TArray<FName> CompletedObjectives;

	UPROPERTY(BlueprintAssignable, Category="Quest")
	FQuestAddDelegate OnQuestAdded;
	
	void AddQuest(const FDataTableRowHandle& QuestRow);
	void AddObjectiveProgression(const FDataTableRowHandle& ObjectiveRow, int32 Count);
	
private:
	TArray<UQuest*> Quests;
	bool HasQuest(const FDataTableRowHandle& QuestRow);
	UQuest* GetQuestFromRow(const FDataTableRowHandle& QuestRow);
	UQuestSubsystem* GetQuestSubsystem() const;

	UFUNCTION()
	void OnQuestCompleted(const FDataTableRowHandle& QuestRow);
	
	UFUNCTION()
	void OnObjectiveCompleted(const FDataTableRowHandle& ObjectiveRow, bool IsObjectiveComplete);
};
