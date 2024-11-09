#include "GameplayTriggerZone.h"
#include "Engine/TriggerBase.h"
#include "Engine.h"
#include "Components/GameFrameworkComponentManager.h"

AGameplayTriggerZone::AGameplayTriggerZone()
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
}

void AGameplayTriggerZone::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (!HasAnyFlags(RF_ClassDefaultObject) && IsValid(GetWorld()) && GetWorld()->IsGameWorld())
	{
		if (UGameFrameworkComponentManager* GameFrameworkSubsys = GetGameInstance()->GetSubsystem<UGameFrameworkComponentManager>())
		{
			GameFrameworkSubsys->AddReceiver(this);
		}
	}
}

void AGameplayTriggerZone::OnInternalVolumeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	int32& Overlaps = OverlappingActors.FindOrAdd(OtherActor, 0);
	Overlaps += 1;

	if (Overlaps == 1)
	{
		OnZoneBeginOverlap.Broadcast(this, OtherActor);
	}
}

void AGameplayTriggerZone::OnInternalVolumeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OverlappingActors.Contains(OtherActor))
	{
		int32& Overlaps = OverlappingActors[OtherActor];

		Overlaps--;

		if (Overlaps <= 0)
		{
			OnZoneEndOverlap.Broadcast(this, OtherActor);
			OverlappingActors.Remove(OtherActor);
		}
	}
}

void AGameplayTriggerZone::BeginPlay()
{
	Super::BeginPlay();

	if (GetLocalRole() == ROLE_Authority)
	{
		for (TSoftObjectPtr<ATriggerBase> TriggerActor : TriggerVolumes)
		{
			if (TriggerActor.IsValid())
			{
				TriggerActor.Get()->GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnInternalVolumeBeginOverlap);
				TriggerActor.Get()->GetCollisionComponent()->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnInternalVolumeEndOverlap);
			}
		}
	}
}

void AGameplayTriggerZone::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		for (TSoftObjectPtr<ATriggerBase> TriggerActor : TriggerVolumes)
		{
			TriggerActor.Get()->GetCollisionComponent()->OnComponentBeginOverlap.RemoveDynamic(this, &ThisClass::OnInternalVolumeBeginOverlap);
			TriggerActor.Get()->GetCollisionComponent()->OnComponentEndOverlap.RemoveDynamic(this, &ThisClass::OnInternalVolumeEndOverlap);
		}
	}

	Super::EndPlay(EndPlayReason);
}
