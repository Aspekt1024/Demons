#pragma once

#include "CoreMinimal.h"
#include "FQuestDataTypes.generated.h"

struct FQuestStage;
struct FQuestObjective;

USTRUCT(BlueprintType)
struct FQuestObjective : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Quests")
	FText ObjectiveDescription;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Quests")
	int32 Quantity;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Quests")
	bool IsOptional;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Quests")
	bool IsPersistent;
};

USTRUCT(BlueprintType)
struct FQuestStage
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Quests")
	FText StageDescription;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Quests")
	TArray<FDataTableRowHandle> Objectives;
};

USTRUCT(BlueprintType)
struct FQuestDetails : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Quests")
	FText QuestName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Quests")
	TArray<FQuestStage> Stages;
};

