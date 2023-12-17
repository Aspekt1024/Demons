#pragma once

#include "CoreMinimal.h"
#include "FQuestDataTypes.h"
#include "FQuest.generated.h"

struct FQuestObjective;
struct FQuestStage;
struct FQuestDetails;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FQuestUpdate);
DECLARE_MULTICAST_DELEGATE_OneParam(FObjectiveCompleteDelegate, const FDataTableRowHandle&);

UCLASS(BlueprintType, Blueprintable)
class UQuest : public UObject
{
	GENERATED_BODY()
	
public:
	void Setup(const FDataTableRowHandle& QuestRow);
	
	UPROPERTY(BlueprintReadOnly)
	FDataTableRowHandle QuestID;

	UPROPERTY(BlueprintReadOnly)
	FQuestDetails QuestDetails;

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentStage;
	
	UPROPERTY(BlueprintReadOnly)
	bool IsQuestComplete;

	UPROPERTY(BlueprintReadOnly)
	TMap<FName, int32> CurrentObjectiveProgress;
	
	UPROPERTY(BlueprintAssignable, Category="Quests")
	FQuestUpdate OnQuestUpdated;

	FObjectiveCompleteDelegate OnObjectiveComplete;
	
	void UpdateObjective(const FDataTableRowHandle& ObjectiveRow, int32 Count);

private:
	void HandleCompletedObjective(const FDataTableRowHandle& ObjectiveRow);
	void SetupStage();
	bool IsStageComplete(FQuestStage StageDetails) const;
	bool IsObjectiveComplete(const FDataTableRowHandle& ObjectiveRow) const;
};
