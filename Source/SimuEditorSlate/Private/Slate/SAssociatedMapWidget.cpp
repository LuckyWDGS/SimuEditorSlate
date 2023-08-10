#include "SAssociatedMapWidget.h"
#include "SimuEditorStyle.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/BlueprintPathsLibrary.h"

void SAssociatedMapWidget::Construct(const FArguments& InArgs)
{
	Path = InArgs._Path;//获取传入的文件夹路径
	TypeMap = InArgs._TypeMap;//获取传入的地图类型
	Arguments = InArgs;
	//字体样式和大小
	FSlateFontInfo EditableTextBoxFont = IPropertyTypeCustomizationUtils::GetBoldFont();
	EditableTextBoxFont.Size = 12;
	ParamWidget.BindLambda([&](FString MapPath) {
		Arguments._OnClick.Execute(MapPath);
		});
	ChildSlot
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			[
				SNew(SButton)
				.HAlign(EHorizontalAlignment::HAlign_Fill)
				.VAlign(EVerticalAlignment::VAlign_Fill)
				.ButtonStyle(&FSimuEditorStyle::Get().GetWidgetStyle<FButtonStyle>("SimuEditorSlate.MapButton"))
				.OnClicked(this,&SAssociatedMapWidget::ExecuteNoParamWidget)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.Padding(0,2,0,2)
					.FillWidth(1.0f)
					.HAlign(EHorizontalAlignment::HAlign_Left)
					.VAlign(EVerticalAlignment::VAlign_Center)
						[
							SNew(STextBlock)
							.Text(InArgs._TextName)
							.MinDesiredWidth(200.0f)
							.Font(EditableTextBoxFont)
							.ColorAndOpacity(FLinearColor(1, 1, 1, 1))
						]
					+ SHorizontalBox::Slot()
						.Padding(0, 0, 10, 0)
						.FillWidth(1.0f)
						.HAlign(EHorizontalAlignment::HAlign_Right)
						.VAlign(EVerticalAlignment::VAlign_Center)
						[
						SNew(STextBlock)
						.Text(InArgs._TextTime)
						.Font(EditableTextBoxFont)
						.ColorAndOpacity(FLinearColor(1, 1, 1, 1))
						]
				]
			]
		];
}

FString SAssociatedMapWidget::GetAssetPath()
{
	FString Left;
	FString Right;
	UKismetStringLibrary::Split(Path, "Content", Left, Right);
	switch (TypeMap)
	{
	case 0:
		return "/Game" + Right + "/UMG/App_" + UBlueprintPathsLibrary::GetBaseFilename(Right);
		break;
	case 1:
		return "/Game" + Right + "/" + UBlueprintPathsLibrary::GetBaseFilename(Right);
		break;
	default:
		return FString();
		break;
	}
}

FReply SAssociatedMapWidget::ExecuteNoParamWidget()
{
	ParamWidget.Execute(GetAssetPath());
	return FReply::Handled();
}
