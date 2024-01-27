#include "CombatComponent.h"

#include "Components/ShapeComponent.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCombatComponent::BeginWatchCollision(UShapeComponent* Collider)
{
	if (Collider == nullptr) return;
	
	Collider->SetGenerateOverlapEvents(true);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &UCombatComponent::BeginOverlap);
}

void UCombatComponent::EndWatchCollision(UShapeComponent* Collider)
{
	if (Collider == nullptr) return;
	
	Collider->SetGenerateOverlapEvents(false);
	Collider->OnComponentBeginOverlap.RemoveDynamic(this, &UCombatComponent::BeginOverlap);
}

void UCombatComponent::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != GetOwner())
	{
		FVector Location;
		const FVector OverlappedLocation = OverlappedComponent->GetComponentLocation();
		OtherComp->GetClosestPointOnCollision(OverlappedLocation, Location);
		const FVector Normal = Location - OverlappedLocation;
		
		TargetHit(OtherActor, Location, Normal);
	}
}

