#pragma once

#include "CoreMinimal.h"
#include "GameplayScenarioAction.h"
#include "GameFeatureAction_AddComponents.h"
#include "GameplayAddComponents.generated.h"

UCLASS()
class BT_NEWGAMEMODERUNTIME_API UGameplayAddComponents : public UGameplayScenarioAction
{
	GENERATED_BODY()
public: 
	UPROPERTY(EditAnywhere, Category = "Components", meta = (TitleProperty = "ComponentClass"))
		TArray<FGameFeatureComponentEntry> ComponentList;

	TArray<TSharedPtr<FComponentRequestHandle>> ComponentRequestHandles;

	virtual void OnScenarioActivated(UScenarioInstanceSubsystem* ScenarioSubsystem) override;
	virtual void OnScenarioDeactivated(UScenarioInstanceSubsystem* ScenarioSubsystem, bool bTearDown) override;
};
