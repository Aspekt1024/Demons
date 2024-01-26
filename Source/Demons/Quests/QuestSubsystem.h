#pragma once

#include "CoreMinimal.h"
#include "QuestSystem.h"
#include "QuestLog.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QuestSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FQuestUpdateDelegate);

UCLASS()
class DEMONS_API UQuestSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	UQuestLog* QuestLog;

	UFUNCTION(BlueprintCallable)
	void RegisterQuestSystem(AQuestSystem* System);
	
	UFUNCTION(BlueprintCallable)
	void AddQuest(FDataTableRowHandle QuestRow);

	UFUNCTION(BlueprintCallable)
	void AddObjectiveProgression(const FDataTableRowHandle& ObjectiveRow, int32 Count);

	UFUNCTION(BlueprintCallable)
	bool IsObjectiveComplete(const FDataTableRowHandle& ObjectiveRow);

	UPROPERTY(BlueprintAssignable, Category="Quest")
	FQuestUpdateDelegate OnQuestUpdated;
};
