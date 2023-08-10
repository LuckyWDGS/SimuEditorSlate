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
	SLATE_ARGUMENT(FText, TextContent)//�ļ�����
	SLATE_ARGUMENT(int32, TextSize)//�����С
	SLATE_END_ARGS()
	/**
	 * Construct this widget
	 *
	 * @param	InArgs	The declaration data for this widget
	 */
	void Construct(const FArguments& InArgs);
	TSharedPtr<STextBlock> TextBlock;
	
};