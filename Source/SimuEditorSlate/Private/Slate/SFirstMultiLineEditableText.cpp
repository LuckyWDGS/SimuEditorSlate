#include "SFirstMultiLineEditableText.h"
#include "SlateColorBrush.h"


void SFirstMultiLineEditableText::Construct(const FArguments& InArgs)
{
	static FSlateColorBrush SlateColorBrush = FSlateColorBrush(FLinearColor(0.25f, 0.25f, 0.25f, 1.0f));

	TSharedPtr<SScrollBar> HorizontalScrollBar;
	TSharedPtr<SScrollBar> VerticalScrollBar;
	ChildSlot
		[
			SNew(SBorder)
			.BorderImage(&SlateColorBrush)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.FillWidth(1)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.FillHeight(1.0f)
						[
							SNew(SMultiLineEditableText)
							.HScrollBar(HorizontalScrollBar)
							.VScrollBar(VerticalScrollBar)
						]
					+ SVerticalBox::Slot()
						.AutoHeight()
						[
							SAssignNew(HorizontalScrollBar, SScrollBar)
							.Orientation(EOrientation::Orient_Horizontal)
						]
				]
					+ SHorizontalBox::Slot()
						.AutoWidth()
						[
						SAssignNew(VerticalScrollBar, SScrollBar)
						.Orientation(EOrientation::Orient_Vertical)
						]
			]
		];
}
