#pragma once

#include "CoreMinimal.h"
#include "GameplayTags.h"
#include "GameFramework/Actor.h"
#include "GameplayTriggerZone.generated.h"

class ATriggerBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGameplayTriggerZoneEvent, AGameplayTriggerZone*, TriggerZone, AActor*, OverlappingActor);

UCLASS()
class BT_NEWGAMEMODERUNTIME_API AGameplayTriggerZone : public AActor, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	AGameplayTriggerZone();

	virtual void PostInitializeComponents() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	TArray<TSoftObjectPtr<ATriggerBase>> TriggerVolumes;

	UFUNCTION()
	virtual void OnInternalVolumeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnInternalVolumeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(BlueprintAssignable)
	FGameplayTriggerZoneEvent OnZoneBeginOverlap;
	UPROPERTY(BlueprintAssignable)
	FGameplayTriggerZoneEvent OnZoneEndOverlap;

	UPROPERTY(EditAnywhere, Category = "Trigger")
	FGameplayTagContainer TriggerTags;

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
	{
		TagContainer.AppendTags(TagContainer);
	}

public:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY()
	TMap<AActor*, int32> OverlappingActors;
};
