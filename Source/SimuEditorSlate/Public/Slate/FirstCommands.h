#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

class FFirstCommands : public TCommands<FFirstCommands>
{

public:
	 FFirstCommands();

	virtual void RegisterCommands() override;

	TSharedPtr<FUICommandInfo> OpenFileCommand;
	TSharedPtr<FUICommandInfo> CloseFileCommand;
	TSharedPtr<FUICommandInfo> SaveFileCommand;
};