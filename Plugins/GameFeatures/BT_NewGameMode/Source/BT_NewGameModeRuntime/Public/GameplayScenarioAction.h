#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayScenarioAction.generated.h"

class UScenarioInstanceSubsystem;

UCLASS(DefaultToInstanced, EditInlineNew, Abstract)
class BT_NEWGAMEMODERUNTIME_API UGameplayScenarioAction : public UObject
{
	GENERATED_BODY()

public:
	virtual void OnScenarioPreActivated(UScenarioInstanceSubsystem* ScenarioSubsystem) {}
	virtual void OnScenarioActivated(UScenarioInstanceSubsystem* ScenarioSubsystem) {}
	virtual void OnScenarioDeactivated(UScenarioInstanceSubsystem* ScenarioSubsystem, bool bTearDown = false) {}
	
};
