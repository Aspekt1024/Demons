#pragma once

#include "CoreMinimal.h"
#include "Demons/Quests/UQuestSubsystem.h"
#include "UInteractionComponent.generated.h"

struct FInteractionDetails;
class UQuestSubsystem;

UCLASS(BlueprintType, Blueprintable)
class DEMONS_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	bool CanInteract;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UDataTable* InteractionTable;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FDataTableRowHandle CompletesObjective;
	
	UFUNCTION(BlueprintCallable)
	void Interact();

	UFUNCTION(BlueprintCallable)
	void SetNonInteractable();

	UFUNCTION(BlueprintImplementableEvent)
	void OnInteract();

	UFUNCTION(BlueprintImplementableEvent)
	void OnInteractionDetermined(FInteractionDetails Interaction);
	
private:
	UPROPERTY()
	UQuestSubsystem* QuestSubsystem;

	FName CurrentInteraction;

	FInteractionDetails* DetermineInteraction() const;
};
