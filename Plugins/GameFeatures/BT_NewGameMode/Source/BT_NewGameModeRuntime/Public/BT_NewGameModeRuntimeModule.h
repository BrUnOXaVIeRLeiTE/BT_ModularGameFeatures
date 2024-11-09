#pragma once

#include "CoreMinimal.h"
#include "EngineMinimal.h"
#include "Modules/ModuleManager.h"

class FBT_NewGameModeRuntimeModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};