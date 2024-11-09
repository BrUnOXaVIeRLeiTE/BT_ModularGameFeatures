#pragma once

#include "CoreMinimal.h"
#include "Engine/NetSerialization.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "Components/GameStateComponent.h"

#include "GamestateScenarioComponent.generated.h"

class UGameplayScenario;

USTRUCT()
struct FGameplayScenarioNetworkArrayItem : public FFastArraySerializerItem
{
	GENERATED_BODY()
public:
	FGameplayScenarioNetworkArrayItem()
	{
		Scenario = nullptr;
		PrevScenario = nullptr;
	}

	UPROPERTY()
	UGameplayScenario* Scenario;

	TWeakObjectPtr<UGameplayScenario> PrevScenario;

	void PreReplicatedRemove(const struct FGameplayScenarioNetworkArray& InArraySerializer);
	void PostReplicatedAdd(const struct FGameplayScenarioNetworkArray& InArraySerializer);
	void PostReplicatedChange(const struct FGameplayScenarioNetworkArray& InArraySerializer);
};

USTRUCT()
struct FGameplayScenarioNetworkArray : public FFastArraySerializer
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TArray<FGameplayScenarioNetworkArrayItem> Items;

	UPROPERTY()
	UGamestateScenarioComponent* ScenarioComp;

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FGameplayScenarioNetworkArrayItem, FGameplayScenarioNetworkArray>(Items, DeltaParms, *this);
	}
};

template <>
struct TStructOpsTypeTraits<FGameplayScenarioNetworkArray> : public TStructOpsTypeTraitsBase2<FGameplayScenarioNetworkArray>
{
	enum
	{
		WithNetDeltaSerializer = true,
	};
};

UCLASS()
class BT_NEWGAMEMODERUNTIME_API UGamestateScenarioComponent : public UGameStateComponent
{
	GENERATED_BODY()

public:
	UGamestateScenarioComponent(const FObjectInitializer& ObjectInitializer);
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void OnRegister() override;

	UFUNCTION()
	virtual void OnScenarioActivated(UGameplayScenario* Scenario);
	UFUNCTION()
	virtual void OnScenarioDeactivated(UGameplayScenario* Scenario);

	UPROPERTY(Replicated)
	FGameplayScenarioNetworkArray Scenarios;

	friend struct FGameplayScenarioNetworkArrayItem;

private:
	void ActivateScenarioLocally(UGameplayScenario* Scenario);
	void DeactivateScenarioLocally(UGameplayScenario* Scenario);
};
