#pragma once

#include "CoreMinimal.h"
#include "GameplayScenarioAction.h"
#include "GameplayActivateScenario.generated.h"

class UGameplayScenario;

UCLASS()
class BT_NEWGAMEMODERUNTIME_API UGameplayActivateScenario : public UGameplayScenarioAction
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowedTypes = "GameplayScenario"))
	TArray<FPrimaryAssetId> Scenarios;

	virtual void OnScenarioPreActivated(UScenarioInstanceSubsystem* ScenarioSubsystem) override;
	virtual void OnScenarioActivated(UScenarioInstanceSubsystem* ScenarioSubsystem) override;
	virtual void OnScenarioDeactivated(UScenarioInstanceSubsystem* ScenarioSubsystem, bool bTearDown) override;
};
