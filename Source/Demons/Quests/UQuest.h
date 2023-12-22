#pragma once

#include "CoreMinimal.h"
#include "FQuestDataTypes.h"
#include "UQuestSubsystem.h"
#include "UQuest.generated.h"

struct FQuestObjective;
struct FQuestStage;
struct FQuestDetails;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FQuestDelegate, const FDataTableRowHandle&, QuestRow);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStageDelegate, const FQuestStage&, StageDetails);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FObjectiveDelegate, const FDataTableRowHandle&, ObjectiveRow, bool, IsObjectiveComplete);

UCLASS(BlueprintType, Blueprintable)
class UQuest : public UObject
{
	GENERATED_BODY()
	
public:
	void Setup(const FDataTableRowHandle& QuestRow, UQuestSubsystem* QuestSS);

	UPROPERTY(BlueprintReadOnly)
	FDataTableRowHandle QuestHandle;

	UPROPERTY(BlueprintReadOnly)
	FQuestDetails QuestDetails;

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentStage;
	
	UPROPERTY(BlueprintReadOnly)
	bool IsQuestComplete;

	UPROPERTY(BlueprintReadOnly)
	TMap<FName, int32> CurrentObjectiveProgress;

	UPROPERTY(BlueprintAssignable)
	FObjectiveDelegate OnObjectiveUpdated;

	UPROPERTY(BlueprintAssignable)
	FQuestDelegate OnQuestCompleted;

	UPROPERTY(BlueprintAssignable)
	FStageDelegate OnStageCompleted;
	
	void AddObjectiveProgression(const FDataTableRowHandle& ObjectiveRow, int32 Count);

private:
	UPROPERTY()
	UQuestSubsystem* QuestSubsystem;
	
	void SetupStage();
	bool IsStageComplete(FQuestStage StageDetails) const;
	bool IsObjectiveComplete(const FDataTableRowHandle& ObjectiveRow) const;
};
