#include "Slate/FirstCommands.h"

#define LOCTEXT_NAMESPACE "FirstCommands"

 FFirstCommands::FFirstCommands()
	:TCommands<FFirstCommands>(
		TEXT("FirstEditor"),//Context name for fast lookup
		NSLOCTEXT("Contexts","FirstEditor","First Editor"),//Localized context name for displaying
		NAME_None,//Parent
		FCoreStyle::Get().GetStyleSetName()//Icon Style Set

	)
{

}

void FFirstCommands::RegisterCommands()
{
	UI_COMMAND(OpenFileCommand,  "OpenFile","OpenFile",  EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::O));
	UI_COMMAND(CloseFileCommand, "CloseFile","CloseFile", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::C));
	UI_COMMAND(SaveFileCommand,  "SaveFile", "SaveFile",  EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::S));

}

#undef LOCTEXT_NAMESPACE
