#pragma once

#include "Widgets/SCanvas.h"

class SFirstCanvas :public SCanvas
{

public:
	/**
	 * Construct this widget
	 *
	 * @param	InArgs	The declaration data for this widget
	 */
	void Construct(const FArguments& InArgs);

	FReply teste();
	FReply teste2();
	FReply teste3(FString In);

	TArray< TSharedPtr<FString>> Options;
	int32 CurrentSelected=-1;

};