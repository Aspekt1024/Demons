#pragma once

#include "CoreMinimal.h"
#include "InteractionsDataTypes.h"
#include "../Quests/QuestSubsystem.h"
#include "InteractionComponent.generated.h"

struct FInteractionTransition;
struct FInteractionDetails;
class UQuestSubsystem;

UCLASS(BlueprintType, Blueprintable)
class DEMONS_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UDataTable* InteractionTable;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FDataTableRowHandle CompletesObjective;

	UPROPERTY(BlueprintReadOnly)
	bool CanInteract;
	
	UPROPERTY(BlueprintReadOnly)
	FName CurrentInteraction;
	
	UFUNCTION(BlueprintCallable)
	void Interact();

	UFUNCTION(BlueprintCallable)
	void SetNonInteractable();

	UFUNCTION(BlueprintCallable)
	void CompleteInteraction(FName InteractionName, bool AllowTransition);

	UFUNCTION(BlueprintImplementableEvent)
	void OnInteract();

	UFUNCTION(BlueprintImplementableEvent)
	void OnInteractionDetermined(FInteractionDetails Interaction);
	
private:
	UPROPERTY()
	UQuestSubsystem* QuestSubsystem;

	TArray<FName> ActionedInteractions;

	FInteractionDetails* DetermineInteraction();
	bool TryProgressInteraction(FInteractionDetails* Interaction);
	FName GetValidInteractionFromTransitions(FInteractionDetails* Interaction) const;
	bool CanTransition(const FInteractionTransition& InteractionTransition) const;
};
