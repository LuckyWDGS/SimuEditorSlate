#include "SFirstCompoundWidget.h"
#include "SFirstButton.h"
#include "SFirstTreeView.h"


void SFirstCompoundWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
		.HAlign(InArgs._HAlign)
		.VAlign(InArgs._VAlign)
		[
			InArgs._Content.Widget
		];
}
