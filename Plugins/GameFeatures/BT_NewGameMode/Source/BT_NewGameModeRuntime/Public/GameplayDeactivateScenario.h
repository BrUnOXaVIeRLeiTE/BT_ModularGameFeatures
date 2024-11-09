#pragma once

#include "CoreMinimal.h"
#include "GameplayScenarioAction.h"
#include "GameplayTags.h"
#include "GameplayDeactivateScenario.generated.h"

UCLASS()
class BT_NEWGAMEMODERUNTIME_API UGameplayDeactivateScenario : public UGameplayScenarioAction
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category="Scenario")
	FGameplayTagQuery DeactivateScenarioQuery;

	virtual void OnScenarioActivated(UScenarioInstanceSubsystem* ScenarioSubsystem);

};
