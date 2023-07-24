#pragma once

#include "CoreMinimal.h"
class FirstEditor
{

public:
	 FirstEditor();

	 TSharedRef<SWidget> MakeMenuBar();

	 TSharedRef<SWidget> MakeToolBar();

	 TSharedPtr<FUICommandList> CommandList;

	 TSharedPtr<SEditableText> EditableText;
};