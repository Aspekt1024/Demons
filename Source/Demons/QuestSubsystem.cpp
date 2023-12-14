// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSubsystem.h"

void UQuestSubsystem::MyBlueprint()
{
	int A = 5;
}

bool UMyBlueprintNode::Handle(float DeltaTime)
{
	this->OnResult.Broadcast(this->TestInt, true);
	return false;
}


UMyBlueprintNode* UMyBlueprintNode::MyBlueprintAsyncCall(int InTestInt)
{
	UMyBlueprintNode* Node = NewObject<UMyBlueprintNode>();
	Node->TestInt = InTestInt;
	return Node;
}

void UMyBlueprintNode::Activate()
{
	//FTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UMyBlueprintNode::Handle), 10.0f);
}