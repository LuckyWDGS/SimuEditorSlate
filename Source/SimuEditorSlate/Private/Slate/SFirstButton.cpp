#include "Slate/SFirstButton.h"
#include "SimuEditorStyle.h"
#include "Slate/SFirstTextBlock.h"


void SFirstButton::Construct(const FArguments& InArgs)
{
	IsNext = InArgs._Next;
	IsFinish = InArgs._Finish;
	Arguments = InArgs;
	OnClicked.BindLambda([&]() {
		if (IsFinish) {
			Arguments._OnClickFinish.Execute();
		}
		else
		{
			Arguments._OnClickNext.Execute(IsNext);
		}
			
		});
	ChildSlot
		[
			SNew(SButton)
			.ButtonStyle(&FSimuEditorStyle::Get().GetWidgetStyle<FButtonStyle>("SimuEditorSlate.ApplicationButtonStyle"))
			.OnClicked(this, &SFirstButton::OnClick)
			.ContentPadding(FMargin(12.0f,4.0f))
			[
				SNew(SFirstTextBlock)
				.TextContent(Arguments._TextContent)
				
			]
		];
	
}

FReply SFirstButton::OnClick()
{
	OnClicked.ExecuteIfBound();
	return FReply::Handled();
}
