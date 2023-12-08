#include "Slate/SFirstCompoundWidget.h"
#include "Slate/SFirstButton.h"
#include "Slate/SFirstTreeView.h"


void SFirstCompoundWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
		.HAlign(InArgs._HAlign)
		.VAlign(InArgs._VAlign)
		[
			InArgs._Content.Widget
		];
}
