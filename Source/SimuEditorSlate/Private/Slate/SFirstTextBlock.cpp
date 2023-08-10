#include "SFirstTextBlock.h"
#include "SimuEditorStyle.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/BlueprintPathsLibrary.h"

void SFirstTextBlock::Construct(const FArguments& InArgs)
{
	
	//字体样式和大小
	FSlateFontInfo EditableTextBoxFont = IPropertyTypeCustomizationUtils::GetBoldFont();
	EditableTextBoxFont.Size = InArgs._TextSize;
	ChildSlot
		[
			SAssignNew(TextBlock,STextBlock)
			.Text(InArgs._TextContent)
			.Font(EditableTextBoxFont)
			.ColorAndOpacity(FLinearColor(1, 1, 1, 1))
		];
}
