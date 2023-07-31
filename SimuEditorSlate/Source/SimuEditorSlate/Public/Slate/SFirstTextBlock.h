#pragma once
#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"


class SFirstTextBlock :public SCompoundWidget
{

public:

	SLATE_BEGIN_ARGS(SFirstTextBlock)
		:_TextSize(12)
	{


	}
	SLATE_ARGUMENT(FText, TextContent)//文件内容
	SLATE_ARGUMENT(int32, TextSize)//字体大小
	SLATE_END_ARGS()
	/**
	 * Construct this widget
	 *
	 * @param	InArgs	The declaration data for this widget
	 */
	void Construct(const FArguments& InArgs);
	TSharedPtr<STextBlock> TextBlock;
	
};