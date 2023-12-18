#pragma once

#include "CoreMinimal.h"
#include "AQuestSystem.h"
#include "Demons/Quests/UQuestLog.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UQuestSubsystem.generated.h"

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

	UPROPERTY(BlueprintAssignable, Category="Quest")
	FQuestUpdateDelegate OnQuestUpdated;
};
