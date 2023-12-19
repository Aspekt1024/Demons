﻿#pragma once

#include "CoreMinimal.h"
#include "FINteractionsDataTypes.generated.h"

struct FInteractionTransition;

USTRUCT(BlueprintType)
struct FInteractionTransition : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Interactions")
	FDataTableRowHandle Interaction;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Interactions")
	TArray<FDataTableRowHandle> RequiredObjectives;
	
};

USTRUCT(BlueprintType)
struct FInteractionDetails : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Interactions")
	FDataTableRowHandle Dialogue;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Interactions")
	FDataTableRowHandle QuestObjective;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Interactions")
	FDataTableRowHandle GiveQuest;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Interactions")
	TArray<FInteractionTransition> TransitionDetails;
};
