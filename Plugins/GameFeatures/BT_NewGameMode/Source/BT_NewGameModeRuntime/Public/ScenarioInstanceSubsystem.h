#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ScenarioInstanceSubsystem.generated.h"

class UGameplayScenario;
class UGameplayChangeMap;
class ULevelStreamingDynamic;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScenarioDelegate, UGameplayScenario*, Scenario);

UCLASS()
class BT_NEWGAMEMODERUNTIME_API UScenarioInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UScenarioInstanceSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category = "Scenario")
	virtual void SetPendingScenario(UGameplayScenario* Scenairo);
	UFUNCTION(BlueprintCallable, Category = "Scenario")
	virtual void TransitionToPendingScenario(bool bForce = false);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scenario")
	TArray<UGameplayScenario*> ActiveScenarios;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scenario")
	UGameplayScenario* PendingScenario;

	UPROPERTY()
	UGameplayScenario* MapTransitionScenario;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Scenario")
	bool bBecomeListenServerFromStandalone;

	UPROPERTY(BlueprintAssignable)
	FScenarioDelegate OnScenarioActivated;

	UPROPERTY(BlueprintAssignable)
	FScenarioDelegate OnScenarioDeactivated;

	friend class UGameplayActivateScenario;
	friend class UGameplayDeactivateScenario;
	friend class UGamestateScenarioComponent;

protected:
	virtual void PreActivateScenario(FPrimaryAssetId ScenarioAsset, bool bForce);
	virtual void PreActivateScenario(UGameplayScenario* Scenario, bool bForce);

	virtual void ActivateScenario(FPrimaryAssetId ScenarioAsset, bool bForce);
	virtual void ActivateScenario(UGameplayScenario* Scenario, bool bForce);

	virtual void DeactivateScenario(UGameplayScenario* Scenario);
	virtual void DeactivateScenario(FPrimaryAssetId ScenarioAsset);

	void TearDownActiveScenarios();

	virtual bool IsScenarioActive(UGameplayScenario* Scenario) const;

	virtual void OnPostLoadMap(UWorld* World);
	virtual void OnPreLoadMap(const FString& MapName);

	void StartActivatingScenario(UGameplayScenario* Scenario, bool bForce);
	void FinishActivatingScenario(UGameplayScenario* Scenario, bool bForce);

	void TransitionToWorld(TObjectPtr<UWorld> World);
};
