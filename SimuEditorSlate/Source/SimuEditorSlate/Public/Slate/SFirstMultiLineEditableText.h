#pragma once

#include "CoreMinimal.h"
#include "Widgets/Text/SMultiLineEditableText.h"

class SFirstMultiLineEditableText :public SCompoundWidget
{

public:
	SLATE_BEGIN_ARGS(SFirstMultiLineEditableText)

	{

	}
	SLATE_END_ARGS()
	/**
	 * Construct this widget
	 *
	 * @param	InArgs	The declaration data for this widget
	 */
	void Construct(const FArguments& InArgs);


};