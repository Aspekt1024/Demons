#pragma once

#include "Abilities/GameplayAbility.h"
#include "DemonsGameplayAbility.generated.h"

UCLASS(BlueprintType, Blueprintable)
class DEMONS_API UDemonsGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	virtual bool CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, FGameplayTagContainer* OptionalRelevantTags) override;
	
};
