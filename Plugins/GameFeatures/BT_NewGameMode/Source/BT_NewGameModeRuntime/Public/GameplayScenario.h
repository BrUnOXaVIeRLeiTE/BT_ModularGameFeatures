#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTags.h"
#include "GameplayScenario.generated.h"

class UGameplayScenarioAction;
class UScenarioInstanceSubsystem;

UCLASS(BlueprintType)
class BT_NEWGAMEMODERUNTIME_API UGameplayScenario : public UPrimaryDataAsset, public IGameplayTagAssetInterface
{
	GENERATED_BODY()
public:
	UGameplayScenario();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actions", meta = (AllowedTypes = "Map"), AssetRegistrySearchable)
	TSoftObjectPtr<UWorld> Map;

	UPROPERTY(EditDefaultsOnly, Instanced, Category = "Actions")
	TArray<UGameplayScenarioAction*> ScenarioActions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", AssetRegistrySearchable)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", AssetRegistrySearchable)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	FGameplayTagContainer ScenarioTags;

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const { TagContainer.AppendTags(ScenarioTags); }

	void PreActivateScenario(UScenarioInstanceSubsystem* ScenarioSubsystem);
	void ActivateScenario(UScenarioInstanceSubsystem* ScenarioSubsystem);
	void DeactivateScenario(UScenarioInstanceSubsystem* ScenarioSubsystem, bool bTearDown = false);

	using Predicate = TFunctionRef<void(UGameplayScenarioAction*)>;
	void ForEachAction_Mutable(Predicate Predicate);

	using ConstPredicate = TFunctionRef<void(const UGameplayScenarioAction*)>;
	void ForEachAction(ConstPredicate Predicate) const;
};
