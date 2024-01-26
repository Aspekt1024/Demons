#pragma once

#include "CoreMinimal.h"
#include "Components/ShapeComponent.h"
#include "CombatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnTargetHitDelegate, AActor*, Target, FVector, Location, FVector, Normal);

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

	UPROPERTY(BlueprintAssignable, Category="Combat")
	FOnTargetHitDelegate OnTargetHit;

	UFUNCTION(BlueprintImplementableEvent, Category="Combat")
	void TargetHit(AActor* Target, FVector Location, FVector Normal);
	
	UFUNCTION(BlueprintCallable)
	void BeginWatchCollision(UShapeComponent* collider);

	UFUNCTION(BlueprintCallable)
	void EndWatchCollision(UShapeComponent* collider);

private:
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
};
