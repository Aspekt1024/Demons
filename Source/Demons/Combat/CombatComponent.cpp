#include "CombatComponent.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCombatComponent::BeginWatchCollision(UShapeComponent* collider)
{
	if (collider == nullptr) return;
	
	collider->SetGenerateOverlapEvents(true);
	collider->OnComponentBeginOverlap.AddDynamic(this, &UCombatComponent::BeginOverlap);
}

void UCombatComponent::EndWatchCollision(UShapeComponent* collider)
{
	if (collider == nullptr) return;
	
	collider->SetGenerateOverlapEvents(false);
	collider->OnComponentBeginOverlap.RemoveDynamic(this, &UCombatComponent::BeginOverlap);
}

void UCombatComponent::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != GetOwner())
	{
		TargetHit(OtherActor, OtherActor->GetActorLocation(), FVector(1.f));
		OnTargetHit.Broadcast(OtherActor, OtherActor->GetActorLocation(), FVector(1.f));
	}
}

