#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AQuestSystem.generated.h"

UCLASS()
class DEMONS_API AQuestSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	AQuestSystem();

	// TODO this is a temporary function while we move things over
	UFUNCTION(BlueprintImplementableEvent)
	void ObjectiveMet();
};
