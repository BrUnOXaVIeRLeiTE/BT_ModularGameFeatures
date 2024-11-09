#pragma once

#include "CoreMinimal.h"
#include "GameplayScenarioAction.h"
#include "GameplayStreamLevelInstance.generated.h"

class ULevelStreamingDynamic;

UCLASS()
class BT_NEWGAMEMODERUNTIME_API UGameplayStreamLevelInstance : public UGameplayScenarioAction
{
	GENERATED_BODY()
public:
	
	virtual void OnScenarioActivated(UScenarioInstanceSubsystem* ScenarioSubsystem) override;
	virtual void OnScenarioDeactivated(UScenarioInstanceSubsystem* ScenarioSubsystem, bool bTearDown) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "World", meta = (AllowedTypes = "Map"))
		TArray<FPrimaryAssetId> StreamedInLevels;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scenario")
		TArray<ULevelStreamingDynamic*> DynamicLevelStreams;
};
