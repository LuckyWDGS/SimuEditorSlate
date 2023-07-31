#pragma once

#include "CoreMinimal.h"


class SFirstCompoundWidget : public SCompoundWidget
{

public:
	
public:
	SLATE_BEGIN_ARGS(SFirstCompoundWidget)
		:_Content()
		,_HAlign(HAlign_Fill)
		,_VAlign(VAlign_Fill)
	{

	}
	SLATE_DEFAULT_SLOT(FArguments, Content)
	SLATE_ARGUMENT(EHorizontalAlignment,HAlign)
	SLATE_ARGUMENT(EVerticalAlignment, VAlign)
	
	SLATE_END_ARGS()

 void Construct(const FArguments& InArgs);
};