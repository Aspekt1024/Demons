#pragma once

#include "CoreMinimal.h"
#include "CombatComponent.generated.h"

UCLASS(BlueprintType, Blueprintable)
class DEMONS_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintImplementableEvent, Category="Combat")
	void TargetHit(AActor* Target, FVector Location, FVector Normal);
	
	UFUNCTION(BlueprintCallable, Category="Combat")
	void BeginWatchCollision(UShapeComponent* Collider);

	UFUNCTION(BlueprintCallable, Category="Combat")
	void EndWatchCollision(UShapeComponent* Collider);

private:
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
};
