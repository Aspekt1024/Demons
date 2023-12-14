// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QuestSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FReturnDelegate, int, StatusCode, bool, Success);

UCLASS()
class DEMONS_API UMyBlueprintNode : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

private:
	UPROPERTY()
	int TestInt;

	bool Handle(float DeltaTime);

public:
	UPROPERTY(BlueprintAssignable)
	FReturnDelegate OnResult;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
		static UMyBlueprintNode* MyBlueprintAsyncCall(int InTestInt);

	virtual void Activate() override;
};

UCLASS()
class DEMONS_API UQuestSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void MyBlueprint();
};
