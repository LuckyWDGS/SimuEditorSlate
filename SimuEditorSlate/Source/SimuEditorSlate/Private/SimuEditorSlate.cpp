// Copyright Epic Games, Inc. All Rights Reserved.

#include "SimuEditorSlate.h"
#include "SimuEditorStyle.h"

#include "FileHelpers.h"

#include "SAssociatedMapWidget.h"
#include "SFirstCompoundWidget.h"
#include "SFirstTextBlock.h"
#include "SFirstButton.h"

#include "Widgets/Layout/SWidgetSwitcher.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/BlueprintPathsLibrary.h"

#include "UnrealExtensionsBPFLibrary.h"


static const FName FSimuEditorSlateTabName("SimuEditorSlate");

#define LOCTEXT_NAMESPACE "FSimuEditorSlateModule"

void FSimuEditorSlateModule::StartupModule()
{
	FSimuEditorStyle::Initialize();
	FSimuEditorStyle::ReloadTextures();

}

void FSimuEditorSlateModule::ShutdownModule()
{
	FSimuEditorStyle::Shutdown();
	
}


void FSimuEditorSlateModule::AssociatedMap()
{

	FString MapPath;
	TSharedPtr<SVerticalBox>VerticalBox;
	TSharedPtr<SOverlay>Overlay;
	//修改滚动条样式
	SAssignNew(ScrollBoxMap, SScrollBox)
		.Style(&FSimuEditorStyle::Get().GetWidgetStyle<FScrollBoxStyle>("SimuEditorSlate.MapScrollBoxStyle"))
		.ScrollBarStyle(&FSimuEditorStyle::Get().GetWidgetStyle<FScrollBarStyle>("SimuEditorSlate.MapScrollBarStyle"));
	TSharedPtr<SEditableTextBox>EditableTextBox;
	FSlateFontInfo EditableTextBoxFont = IPropertyTypeCustomizationUtils::GetBoldFont();
	EditableTextBoxFont.Size = 12;
	OnTextSearchMap(FText::FromString(""), ETextCommit::OnEnter);
		SAssignNew(VerticalBox, SVerticalBox)//在此处定义生成。在之上引用为空指针。是因为这个对象本来就没有创建出来（安全）
		+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(20,20,20,0)
			[
			SAssignNew(EditableTextBox, SEditableTextBox)
			.HintText(FText::FromString(L"搜索"))
			.Justification(ETextJustify::Left)
			.Font(FSlateFontInfo(EditableTextBoxFont))
			.Style(&FSimuEditorStyle::Get().GetWidgetStyle<FEditableTextBoxStyle>("SimuEditorSlate.MapEditableTextBox"))
			.OnTextCommitted_Raw(this, &FSimuEditorSlateModule::OnTextSearchMap)
			]
		+ SVerticalBox::Slot()
			.FillHeight(1.0f)
			.Padding(20, 20, 20, 10)
		[
			ScrollBoxMap.ToSharedRef()
		];

		FSlateBrush* Image = FCoreStyle::Get().GetDefaultBrush();
		Image->ImageSize = FVector2D(500, 660);
		SAssignNew(Overlay, SOverlay)
			+ SOverlay::Slot()
			[
				SNew(SImage)
				
				.Image(Image)
				.Visibility(EVisibility::Hidden)
			]
			+SOverlay::Slot()

			[
				VerticalBox.ToSharedRef()
			];
	//弹出对话框
		SAssignNew(FirstCustomDialog,SFirstCustomDialog)
		.Title(FText::FromString(L"地图列表"))
		.UseScrollBox(false)
		.SizingRule(ESizingRule::FixedSize)
		.ClientSize(FVector2D(500,660))
		.DialogContent(
			Overlay
						);
		FirstCustomDialog->ShowModal();
}



void FSimuEditorSlateModule::OpenTheApps()
{
	FString MapPath;
	TSharedPtr<SVerticalBox>VerticalBox;
	TSharedPtr<SOverlay>Overlay;
	SAssignNew(ScrollBoxMap, SScrollBox)
		
		.Style(&FSimuEditorStyle::Get().GetWidgetStyle<FScrollBoxStyle>("SimuEditorSlate.MapScrollBoxStyle"))
		.ScrollBarStyle(&FSimuEditorStyle::Get().GetWidgetStyle<FScrollBarStyle>("SimuEditorSlate.MapScrollBarStyle"));
	TSharedPtr<SEditableTextBox>EditableTextBox;
	FSlateFontInfo EditableTextBoxFont = IPropertyTypeCustomizationUtils::GetBoldFont();
	EditableTextBoxFont.Size = 12;
	OnTextSearchOpenTheApp(FText::FromString(""), ETextCommit::OnEnter);
	SAssignNew(VerticalBox, SVerticalBox)//在此处定义生成。在之上引用为空指针。是因为这个对象本来就没有创建出来（安全）
	+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(20, 20, 20, 0)
		[
			SAssignNew(EditableTextBox, SEditableTextBox)
			.HintText(FText::FromString(L"搜索"))
		.Justification(ETextJustify::Left)
		.Font(FSlateFontInfo(EditableTextBoxFont))
		.Style(&FSimuEditorStyle::Get().GetWidgetStyle<FEditableTextBoxStyle>("SimuEditorSlate.MapEditableTextBox"))
		.OnTextCommitted_Raw(this, &FSimuEditorSlateModule::OnTextSearchOpenTheApp)
		]
	+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		.Padding(20, 20, 20, 10)
		[
			ScrollBoxMap.ToSharedRef()
		];

	FSlateBrush* Image = FCoreStyle::Get().GetDefaultBrush();
	Image->ImageSize = FVector2D(500, 660);
	SAssignNew(Overlay, SOverlay)
		+ SOverlay::Slot()
		[
			SNew(SImage)

			.Image(Image)
		.Visibility(EVisibility::Hidden)
		]
	+ SOverlay::Slot()
		[
			VerticalBox.ToSharedRef()
		];
	//弹出对话框
	SAssignNew(FirstCustomDialog, SFirstCustomDialog)
		.Title(FText::FromString(L"应用列表"))
		.UseScrollBox(false)
		.SizingRule(ESizingRule::FixedSize)
		.ClientSize(FVector2D(500, 660))
		.DialogContent(
			Overlay
		);
	FirstCustomDialog->ShowModal();
}

void FSimuEditorSlateModule::OnTextSearchOpenTheApp(const FText& InText, ETextCommit::Type CommitInfo)
{
	if (ETextCommit::OnEnter)
	{
		ScrollBoxMap->ClearChildren();
		FString FindDirectoryPath = UKismetSystemLibrary::GetProjectContentDirectory() + "Apps";
		TArray<FSlateMapData>MapData = USimuEditorSlateBPF::LoadMapToFind(FindDirectoryPath, InText.ToString(), InText.IsEmpty(), 0);
		for (auto Data : MapData)
		{
			ScrollBoxMap->AddSlot()
				[
					SNew(SAssociatedMapWidget)
					.TextName(FText::FromString(Data.MapName))
					.TextTime(FText::FromString(Data.ModificationTime))
					.Path(Data.DirectoryPath)
					.TypeMap(Data.TypeMap)
					.OnClick_Lambda([&](FString MapPath) {
						FSlateApplication::Get().RequestDestroyWindow(FirstCustomDialog.ToSharedRef());
						OpenTheApp->OnCompleted.Broadcast(MapPath);
					})
				];
		}
	}
}

void FSimuEditorSlateModule::Applications()
{
	AllowNext = false;
	IsUINext = false;
	TSharedPtr<SOverlay>Overlay;
	FSlateBrush* Image = FCoreStyle::Get().GetDefaultBrush();
	Image->ImageSize = FVector2D(740, 460);
	SAssignNew(WidgetSwitcher, SWidgetSwitcher);
	FSlateFontInfo EditableTextBoxFont = IPropertyTypeCustomizationUtils::GetBoldFont();
	EditableTextBoxFont.Size = 12;
	SAssignNew(LoadMapSScrollBox, SScrollBox)
		.Style(&FSimuEditorStyle::Get().GetWidgetStyle<FScrollBoxStyle>("SimuEditorSlate.MapScrollBoxStyle"))
		.ScrollBarStyle(&FSimuEditorStyle::Get().GetWidgetStyle<FScrollBarStyle>("SimuEditorSlate.MapScrollBarStyle"));
	FindAllLoadMap();
	SAssignNew(Overlay, SOverlay)
		+ SOverlay::Slot()
		[
			SNew(SImage)
			.Image(Image)
		.Visibility(EVisibility::Hidden)
		]
	+ SOverlay::Slot()

		[
			WidgetSwitcher.ToSharedRef()
		];

	//WidgetSwitch 内容0
	WidgetSwitcher->AddSlot(0)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			[
				SNew(SImage)
				.Image(FSimuEditorStyle::Get().GetBrush("SimuEditorSlate.xiangdao"))
			]
			+ SOverlay::Slot()
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.Padding(300,40,0,0)
				.HAlign(EHorizontalAlignment::HAlign_Left)
				.VAlign(EVerticalAlignment::VAlign_Fill)
				.AutoHeight()
				[
					SNew(SFirstTextBlock)
					.TextContent(FText::FromString(L"欢迎来到公路交通数字李生应用制作向导"))
					.TextSize(16)
				]
				+ SVerticalBox::Slot()
				.Padding(300,50,0,0)
				.AutoHeight()
				[
					SNew(SFirstTextBlock)
					.TextContent(FText::FromString(L"一个交通数字李生应用由两部分组成:地图及UI逻辑。"))
				]
				+ SVerticalBox::Slot()
				.Padding(300, 20, 0, 0)

					[
						SNew(SFirstTextBlock)
						.TextContent(FText::FromString(L"单击“下一步”继续，或是点击关闭按钮退出编辑器。"))
					]
				+ SVerticalBox::Slot()
					.FillHeight(1.0f)
					.HAlign(EHorizontalAlignment::HAlign_Left)
					.VAlign(EVerticalAlignment::VAlign_Bottom)
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot()
						.Padding(620,0,0,10)
						.AutoWidth()
						[	
							SNew(SFirstButton)
							.TextContent(FText::FromString(L"下一步>"))
							.OnClickNext_Raw(this,&FSimuEditorSlateModule::SwidgetIndex)
						]
					]
				]
		];
		WidgetSwitcher->AddSlot(1)
		[
				SNew(SOverlay)
				+SOverlay::Slot()
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.Padding(60,25,0,0)
				.AutoHeight()
				[
				SNew(SFirstTextBlock)
				.TextContent(FText::FromString(L"关联地图（1/2）"))
				.TextSize(16)
				]
				+ SVerticalBox::Slot()
				.Padding(100, 10, 0, 0)
				.AutoHeight()
				[
				SNew(SFirstTextBlock)
				.TextContent(FText::FromString(L"地图构成了数字李生应用的三维静态场景，包括道路、标识以及周边环境等。"))
				]
				+ SVerticalBox::Slot()
				.Padding(100, 10, 0, 0)
				.AutoHeight()
				[
				SNew(SFirstTextBlock)
				.TextContent(FText::FromString(L"这里，您可以为应用新建一个地图，或者从已有的地图资源中选择"))
				]
				+ SVerticalBox::Slot()
				.Padding(100, 10, 0, 0)
				.AutoHeight()
				[
				SNew(SFirstTextBlock)
				.TextContent(FText::FromString(L"后续，您可以在地图窗口找到它，并通过组合地图元素的方式编辑您的地图。"))
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.Padding(100, 10, 0, 5)
					.AutoWidth()
					[
						SAssignNew(NewMapCheckBox, SCheckBox)
						.IsChecked(ECheckBoxState::Checked)
						.OnCheckStateChanged_Raw(this,&FSimuEditorSlateModule::OnCheckStateNewMap)
						[
							SNew(SFirstTextBlock)
						.TextContent(FText::FromString(L"新建地图名称："))
						]
					]						
					+ SHorizontalBox::Slot()
					.FillWidth(1)
					.VAlign(EVerticalAlignment::VAlign_Bottom)
					[
						SAssignNew(NewMapHorizontalBox, SHorizontalBox)
						+ SHorizontalBox::Slot()
						.FillWidth(0.8)
						[
							SNew(SEditableTextBox)
							.HintText(FText::FromString(L"仅支持输入字母、数字              "))
							.Justification(ETextJustify::Left)
							.Font(FSlateFontInfo(EditableTextBoxFont))
							.Style(&FSimuEditorStyle::Get().GetWidgetStyle<FEditableTextBoxStyle>("SimuEditorSlate.MapEditableTextBox"))
							.OnTextChanged_Raw(this, &FSimuEditorSlateModule::OnTextNewMapChanged)
							.OnTextCommitted_Raw(this,&FSimuEditorSlateModule::OnTextSearchNewMap)
						]
						+ SHorizontalBox::Slot()
						.Padding(20,0,0,0)
						.FillWidth(1.2)
						[
							SAssignNew(NewMapFirstTextBlock, SFirstTextBlock)
						]
					]
				]

				+ SVerticalBox::Slot()
				.Padding(0, 10, 0, -180)
				.FillHeight(1)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.Padding(100,0,0,0)
					.AutoWidth()
					.VAlign(EVerticalAlignment::VAlign_Top)
					[
						SAssignNew(LoadMapCheckBox, SCheckBox)
						.OnCheckStateChanged_Raw(this, &FSimuEditorSlateModule::OnCheckStateLoadMap)
						[
							SNew(SFirstTextBlock)
							.TextContent(FText::FromString(L"关联已有地图："))
						]
					]
				+ SHorizontalBox::Slot()
					.Padding(0, 0, 5, 10)
					.FillWidth(1)
					.HAlign(EHorizontalAlignment::HAlign_Fill)
					[
						LoadMapSScrollBox.ToSharedRef()
					]
				]
				+ SVerticalBox::Slot()
					.FillHeight(1)
					.HAlign(EHorizontalAlignment::HAlign_Left)
					.VAlign(EVerticalAlignment::VAlign_Bottom)
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot()
					.Padding(620, 0, 0, 10)
					.AutoWidth()
					.HAlign(EHorizontalAlignment::HAlign_Left)
						[
						SNew(SFirstButton)
						.TextContent(FText::FromString(L"下一步>"))
						.OnClickNext_Lambda([&](bool IsNext) {
							if (AllowNext&& NewMapCheckBox->IsChecked()) {
							LoadMapNext(LoadMapName);
					}
							})
						]
						+ SHorizontalBox::Slot()
						.Padding(-200, 0, 0, 10)
						.AutoWidth()
						.HAlign(EHorizontalAlignment::HAlign_Left)
						[
						SNew(SFirstButton)
						.TextContent(FText::FromString(L"<上一步"))
						.Next(false)
						.OnClickNext_Raw(this, &FSimuEditorSlateModule::SwidgetIndex)
						]
					]
				]
			];

			WidgetSwitcher->AddSlot(2)
				[
					SNew(SOverlay)
					+ SOverlay::Slot()
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
				.Padding(60, 25, 0, 0)
				.AutoHeight()
				[
					SNew(SFirstTextBlock)
					.TextContent(FText::FromString(L"UI逻辑（2/2）"))
				.TextSize(16)
				]
			+ SVerticalBox::Slot()
				.Padding(100, 10, 0, 0)
				.AutoHeight()
				[
					SNew(SFirstTextBlock)
					.TextContent(FText::FromString(L"UI逻辑构成了数字李生应用的UI交互以及应用逻辑。这通常定义了动态的车"))
				]
			+ SVerticalBox::Slot()
				.Padding(100, 10, 0, 0)
				.AutoHeight()
				[
					SNew(SFirstTextBlock)
					.TextContent(FText::FromString(L"流行为、环境变化以及数据呈现。后续可以在与应用名同名的窗口中找到它，"))
				]
			+ SVerticalBox::Slot()
				.Padding(100, 10, 0, 0)
				.AutoHeight()
				[
					SNew(SFirstTextBlock)
					.TextContent(FText::FromString(L"并添加UI组件、算法或者其他应用逻辑。"))
				]
			+ SVerticalBox::Slot()
				.Padding(100, 40, 0, 0)
				.AutoHeight()
				[
					SNew(SFirstTextBlock)
					.TextContent(FText::FromString(L"现在，请为您的应用取一个名字。"))
				]
			+ SVerticalBox::Slot()
				.Padding(0, 10, 0, 0)
				.AutoHeight()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
				.Padding(140, 0, 0, 5)
				.AutoWidth()
				[
					SNew(SFirstTextBlock)
					.TextContent(FText::FromString(L"应用名称："))
				]
			+ SHorizontalBox::Slot()
				.FillWidth(0.8)
				.VAlign(EVerticalAlignment::VAlign_Bottom)
				[
					SNew(SEditableTextBox)
					.HintText(FText::FromString(L"仅支持输入字母、数字              "))
					.Justification(ETextJustify::Left)
					.Font(FSlateFontInfo(EditableTextBoxFont))
					.Style(&FSimuEditorStyle::Get().GetWidgetStyle<FEditableTextBoxStyle>("SimuEditorSlate.MapEditableTextBox"))
					.OnTextChanged_Raw(this, &FSimuEditorSlateModule::OnTextUIChanged)
					.OnTextCommitted_Raw(this, &FSimuEditorSlateModule::OnTextSearchUI)
				]
			+ SHorizontalBox::Slot()
				.Padding(20, 0, 0, 0)
				.VAlign(EVerticalAlignment::VAlign_Bottom)
				.FillWidth(1.2)
				[
					SAssignNew(UIFirstTextBlock, SFirstTextBlock)
				]
				]
			+ SVerticalBox::Slot()
				.FillHeight(1)
				.HAlign(EHorizontalAlignment::HAlign_Left)
				.VAlign(EVerticalAlignment::VAlign_Bottom)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
				.Padding(620, 0, 0, 10)
				.AutoWidth()
				.HAlign(EHorizontalAlignment::HAlign_Left)
				[
					SNew(SFirstButton)
					.TextContent(FText::FromString(L"下一步>"))
				.OnClickNext_Lambda([&](bool IsNext) {
					if (IsUINext) {
					UINext(UIName);
					}
					})
				]
			+ SHorizontalBox::Slot()
				.Padding(-200, 0, 0, 10)
				.AutoWidth()
				.HAlign(EHorizontalAlignment::HAlign_Left)
				[
					SNew(SFirstButton)
					.TextContent(FText::FromString(L"<上一步"))
				.Next(false)
				.OnClickNext_Raw(this, &FSimuEditorSlateModule::SwidgetIndex)
				]
				]
				]
				];

	//LoadMap
	OnCheckStateNewMap(ECheckBoxState::Checked);
	//弹出对话框
	SAssignNew(FirstCustomDialog, SFirstCustomDialog)
		.Title(FText::FromString(L"应用向导"))
		.UseScrollBox(false)
		.SizingRule(ESizingRule::FixedSize)
		.ClientSize(FVector2D(740, 460))
		.DialogContent(
			Overlay
		);
	FirstCustomDialog->ShowModal();

}

void FSimuEditorSlateModule::SwidgetIndex(const bool NextIndex)
{
	int32 CurrentIndex=0;
	switch (NextIndex)
	{
	case true:
		CurrentIndex= WidgetSwitcher->GetActiveWidgetIndex()+1;
		break;
	case false:
		CurrentIndex = WidgetSwitcher->GetActiveWidgetIndex() - 1;
		break;
	}

	if (CurrentIndex >=0 && CurrentIndex < WidgetSwitcher->GetNumWidgets()){

		WidgetSwitcher->SetActiveWidgetIndex(CurrentIndex);
	
	}
}

void FSimuEditorSlateModule::LoadMapNext(FString LoadMapNames)
{
	LoadMapName = LoadMapNames;
	SwidgetIndex(true);
}

void FSimuEditorSlateModule::OnTextNewMapChanged(const FText& InText)
{
	LoadMapName = InText.ToString();
	AllowNext = true;
	FText Default = FText::FromString(L"0/20");
	FString NewName = InText.ToString();
	FString Exists = UKismetSystemLibrary::GetProjectContentDirectory() + "Carla/Maps/" + NewName;
	TArray<FString>Result;
	if (NewName.IsEmpty()) {
		NewMapFirstTextBlock->TextBlock->SetText(Default);
		NewMapFirstTextBlock->TextBlock->SetColorAndOpacity(FLinearColor(0, 1, 0, 1));
		AllowNext = false;
	}
	else if (!UUnrealExtensionsBPFLibrary::RegexMatch(NewName, "^[A-Za-z0-9]+$", Result)) {
		FText Error = FText::FromString(L"仅支持输入字母、数字");
		NewMapFirstTextBlock->TextBlock->SetText(Error);
		NewMapFirstTextBlock->TextBlock->SetColorAndOpacity(FLinearColor(1, 0, 0, 1));
		AllowNext = false;
	}
	else if (UBlueprintPathsLibrary::DirectoryExists(Exists)) {
		FText Error = FText::FromString(L"当前名称已占用");
		NewMapFirstTextBlock->TextBlock->SetText(Error);
		NewMapFirstTextBlock->TextBlock->SetColorAndOpacity(FLinearColor(1, 0, 0, 1));
		AllowNext = false;
	}

	else if (NewName.Len() <= 20 && UUnrealExtensionsBPFLibrary::RegexMatch(NewName, "^[A-Za-z0-9]+$", Result)) {
			NewMapFirstTextBlock->TextBlock->SetText(FText::FromString(FString::FromInt(NewName.Len()) + "/20"));
			NewMapFirstTextBlock->TextBlock->SetColorAndOpacity(FLinearColor(0, 1, 0, 1));
		}
	else{
		NewMapFirstTextBlock->TextBlock->SetText(FText::FromString(FString::FromInt(NewName.Len()) + "/20"));
		NewMapFirstTextBlock->TextBlock->SetColorAndOpacity(FLinearColor(1, 0, 0, 1));
		AllowNext = false;
	}
}

void FSimuEditorSlateModule::OnCheckStateNewMap(ECheckBoxState InNewState)
{
	switch (InNewState)
	{
	case ECheckBoxState::Unchecked:
		NewMapHorizontalBox->SetVisibility(EVisibility::Hidden);
		LoadMapSScrollBox->SetVisibility(EVisibility::Visible);
		LoadMapCheckBox->SetIsChecked(ECheckBoxState::Checked);
		break;
	case ECheckBoxState::Checked:
		NewMapHorizontalBox->SetVisibility(EVisibility::Visible);
		LoadMapSScrollBox->SetVisibility(EVisibility::Hidden);
		LoadMapCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
		break;
	}
}

void FSimuEditorSlateModule::OnTextSearchNewMap(const FText& InText, ETextCommit::Type CommitInfo)
{
	if (CommitInfo==ETextCommit::OnEnter && AllowNext) {
		LoadMapNext(InText.ToString());
	}
}

void FSimuEditorSlateModule::FindAllLoadMap()
{
	FString InText = L"";
	LoadMapSScrollBox->ClearChildren();
	FString FindDirectoryPath = UKismetSystemLibrary::GetProjectContentDirectory() + "Carla/Maps";
	TArray<FSlateMapData>MapData = USimuEditorSlateBPF::LoadMapToFind(FindDirectoryPath, InText, InText.IsEmpty(), 1);
	for (auto Data : MapData)
	{
		LoadMapSScrollBox->AddSlot()
			[
			SNew(SAssociatedMapWidget)
			.TextName(FText::FromString(Data.MapName))
			.TextTime(FText::FromString(Data.ModificationTime))
			.Path(Data.DirectoryPath)
			.TypeMap(Data.TypeMap)
			.OnClick_Lambda([&](FString MapPath) {
			LoadMapNext(UBlueprintPathsLibrary::GetBaseFilename(MapPath));
				})
			];
	}
	
}

void FSimuEditorSlateModule::OnCheckStateLoadMap(ECheckBoxState InNewState)
{
	switch (InNewState)
	{
	case ECheckBoxState::Unchecked:
		LoadMapSScrollBox->SetVisibility(EVisibility::Hidden);
		NewMapHorizontalBox->SetVisibility(EVisibility::Visible);
		NewMapCheckBox->SetIsChecked(ECheckBoxState::Checked);
		break;
	case ECheckBoxState::Checked:
		LoadMapSScrollBox->SetVisibility(EVisibility::Visible);
		NewMapHorizontalBox->SetVisibility(EVisibility::Hidden);
		NewMapCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
		break;
	}
}

void FSimuEditorSlateModule::UINext(FString UINames)
{
	UIName = UINames;
	Application->OnCompleted.Broadcast(NewMapCheckBox->IsChecked(), LoadMapName, UIName);
	FSlateApplication::Get().RequestDestroyWindow(FirstCustomDialog.ToSharedRef());

}

void FSimuEditorSlateModule::OnTextUIChanged(const FText& InText)
{

	UIName = InText.ToString();
	IsUINext = true;
	FText Default = FText::FromString(L"0/20");
	FString NewName = InText.ToString();
	FString Exists = UKismetSystemLibrary::GetProjectContentDirectory() + "Apps/" + NewName;
	TArray<FString>Result;
	if (NewName.IsEmpty()) {
		UIFirstTextBlock->TextBlock->SetText(Default);
		UIFirstTextBlock->TextBlock->SetColorAndOpacity(FLinearColor(0, 1, 0, 1));
		IsUINext = false;
	}
	else if (!UUnrealExtensionsBPFLibrary::RegexMatch(NewName, "^[A-Za-z0-9]+$", Result)) {
		FText Error = FText::FromString(L"仅支持输入字母、数字");
		UIFirstTextBlock->TextBlock->SetText(Error);
		UIFirstTextBlock->TextBlock->SetColorAndOpacity(FLinearColor(1, 0, 0, 1));
		IsUINext = false;
	}
	else if (UBlueprintPathsLibrary::DirectoryExists(Exists)) {
		FText Error = FText::FromString(L"当前名称已占用");
		UIFirstTextBlock->TextBlock->SetText(Error);
		UIFirstTextBlock->TextBlock->SetColorAndOpacity(FLinearColor(1, 0, 0, 1));
		IsUINext = false;
	}

	else if (NewName.Len() <= 20 && UUnrealExtensionsBPFLibrary::RegexMatch(NewName, "^[A-Za-z0-9]+$", Result)) {
		UIFirstTextBlock->TextBlock->SetText(FText::FromString(FString::FromInt(NewName.Len()) + "/20"));
		UIFirstTextBlock->TextBlock->SetColorAndOpacity(FLinearColor(0, 1, 0, 1));
	}
	else {
		UIFirstTextBlock->TextBlock->SetText(FText::FromString(FString::FromInt(NewName.Len()) + "/20"));
		UIFirstTextBlock->TextBlock->SetColorAndOpacity(FLinearColor(1, 0, 0, 1));
		IsUINext = false;
	}

}

void FSimuEditorSlateModule::OnTextSearchUI(const FText& InText, ETextCommit::Type CommitInfo)
{
	if (CommitInfo == ETextCommit::OnEnter && IsUINext) {
		UINext(InText.ToString());
	}
}

void FSimuEditorSlateModule::FinishWizard()
{
	TSharedPtr<SOverlay>Overlay;
	FSlateBrush* Image = FCoreStyle::Get().GetDefaultBrush();
	Image->ImageSize = FVector2D(740, 460);
	SAssignNew(WidgetSwitcher, SWidgetSwitcher);
	SAssignNew(Overlay, SOverlay)
		+ SOverlay::Slot()
		[
			SNew(SImage)
			.Image(Image)
		.Visibility(EVisibility::Hidden)
		]
	+ SOverlay::Slot()

		[
			WidgetSwitcher.ToSharedRef()
		];

	//WidgetSwitch 内容0
	WidgetSwitcher->AddSlot(0)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
		[
			SNew(SImage)
			.Image(FSimuEditorStyle::Get().GetBrush("SimuEditorSlate.xiangdao"))
		]
	+ SOverlay::Slot()
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
		.Padding(300, 40, 0, 0)
		.AutoHeight()
		[
			SNew(SFirstTextBlock)
			.TextContent(FText::FromString(L"向导已完成"))
		.TextSize(16)
		]
	+ SVerticalBox::Slot()
		.Padding(300, 50, 0, 0)
		.AutoHeight()
		[
			SNew(SFirstTextBlock)
			.TextContent(FText::FromString(L"一切准备就绪。"))
		]
	+ SVerticalBox::Slot()
		.Padding(300, 20, 0, 0)

		[
			SNew(SFirstTextBlock)
			.TextContent(FText::FromString(L"单击“完成”关闭向导，开始编辑应用。"))
		]
	+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		.HAlign(EHorizontalAlignment::HAlign_Left)
		.VAlign(EVerticalAlignment::VAlign_Bottom)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
		.Padding(620, 0, 0, 10)
		.AutoWidth()
		[
			SNew(SFirstButton)
			.Finish(true)
			.TextContent(FText::FromString(L"完  成"))
			.OnClickFinish_Lambda([&]() {
				FinishComplete->OnCompleted.Broadcast();
				FSlateApplication::Get().RequestDestroyWindow(FirstCustomDialog.ToSharedRef());
				})
			
		]
		]
		]
		];

	//弹出对话框
	SAssignNew(FirstCustomDialog, SFirstCustomDialog)
		.Title(FText::FromString(L"应用向导"))
		.UseScrollBox(false)
		.SizingRule(ESizingRule::FixedSize)
		.ClientSize(FVector2D(740, 460))
		.DialogContent(
			Overlay
		);
	FirstCustomDialog->ShowModal();


}

void FSimuEditorSlateModule::OnTextSearchMap(const FText& InText, ETextCommit::Type CommitInfo)
{
	if (ETextCommit::OnEnter)
	{
		ScrollBoxMap->ClearChildren();
		FString FindDirectoryPath = UKismetSystemLibrary::GetProjectContentDirectory() + "Carla/Maps";
		TArray<FSlateMapData>MapData=USimuEditorSlateBPF::LoadMapToFind(FindDirectoryPath, InText.ToString(), InText.IsEmpty(),1);
		for (auto Data : MapData)
		{
			ScrollBoxMap->AddSlot()
				[
					SNew(SAssociatedMapWidget)
					.TextName(FText::FromString(Data.MapName))
					.TextTime(FText::FromString(Data.ModificationTime))
					.Path(Data.DirectoryPath)
					.TypeMap(Data.TypeMap)
					.OnClick_Lambda([&](FString MapPath) {
						FSlateApplication::Get().RequestDestroyWindow(FirstCustomDialog.ToSharedRef());
						ConntectionMap->OnCompleted.Broadcast(MapPath);
						})
				];
		}
	}
}


void FSimuEditorSlateModule::InitApps()
{
	FString MapPath;
	TSharedPtr<SVerticalBox>VerticalBox;
	TSharedPtr<SOverlay>Overlay;
	SAssignNew(ScrollBoxMap, SScrollBox)
		.Style(&FSimuEditorStyle::Get().GetWidgetStyle<FScrollBoxStyle>("SimuEditorSlate.MapScrollBoxStyle"))
		.ScrollBarStyle(&FSimuEditorStyle::Get().GetWidgetStyle<FScrollBarStyle>("SimuEditorSlate.MapScrollBarStyle"));
	TSharedPtr<SEditableTextBox>EditableTextBox;
	FSlateFontInfo EditableTextBoxFont = IPropertyTypeCustomizationUtils::GetBoldFont();
	EditableTextBoxFont.Size = 12;
	OnTextSearchInitApps(FText::FromString(""), ETextCommit::OnEnter);
	SAssignNew(VerticalBox, SVerticalBox)//在此处定义生成。在之上引用为空指针。是因为这个对象本来就没有创建出来（安全）
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(20, 20, 20, 0)
		[
			SAssignNew(EditableTextBox, SEditableTextBox)
			.HintText(FText::FromString(L"搜索"))
		.Justification(ETextJustify::Left)
		.Font(FSlateFontInfo(EditableTextBoxFont))
		.Style(&FSimuEditorStyle::Get().GetWidgetStyle<FEditableTextBoxStyle>("SimuEditorSlate.MapEditableTextBox"))
		.OnTextCommitted_Raw(this, &FSimuEditorSlateModule::OnTextSearchInitApps)
		]
	+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		.Padding(20, 20, 20, 10)
		[
			ScrollBoxMap.ToSharedRef()
		]
	+SVerticalBox::Slot()
		.FillHeight(1.0f)
		.Padding(20, 15, 20, 20)
		.AutoHeight()
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
		.HAlign(EHorizontalAlignment::HAlign_Right)
		[
			SNew(SFirstButton)
			.TextContent(FText::FromString(L"新建应用"))
		.Finish(true)
		.OnClickFinish_Lambda([&]() {
		MapPath = NULL;
		FSlateApplication::Get().RequestDestroyWindow(FirstCustomDialog.ToSharedRef());
		InitTheApp->OnCompleted.Broadcast(MapPath);
			})
		]
		];
	FSlateBrush* Image = FCoreStyle::Get().GetDefaultBrush();
	Image->ImageSize = FVector2D(500, 660);
	SAssignNew(Overlay, SOverlay)
		+ SOverlay::Slot()
		[
			SNew(SImage)

			.Image(Image)
		.Visibility(EVisibility::Hidden)
		]
	+ SOverlay::Slot()
		[
			VerticalBox.ToSharedRef()
		];
	//弹出对话框
	SAssignNew(FirstCustomDialog, SFirstCustomDialog)
		.Title(FText::FromString(L"初始列表"))
		.UseScrollBox(false)
		.SizingRule(ESizingRule::FixedSize)
		.ClientSize(FVector2D(500, 660))
		.DialogContent(
			Overlay
		);
	FirstCustomDialog->ShowModal();
}

void FSimuEditorSlateModule::OnTextSearchInitApps(const FText& InText, ETextCommit::Type CommitInfo)
{
	if (ETextCommit::OnEnter)
	{
		ScrollBoxMap->ClearChildren();
		FString FindDirectoryPath = UKismetSystemLibrary::GetProjectContentDirectory() + "Apps";
		TArray<FSlateMapData>MapData = USimuEditorSlateBPF::LoadMapToFind(FindDirectoryPath, InText.ToString(), InText.IsEmpty(), 0);
		for (auto Data : MapData)
		{
			ScrollBoxMap->AddSlot()
				[
					SNew(SAssociatedMapWidget)
					.TextName(FText::FromString(Data.MapName))
				.TextTime(FText::FromString(Data.ModificationTime))
				.Path(Data.DirectoryPath)
				.TypeMap(Data.TypeMap)
				.OnClick_Lambda([&](FString MapPath) {
				FSlateApplication::Get().RequestDestroyWindow(FirstCustomDialog.ToSharedRef());
				InitTheApp->OnCompleted.Broadcast(MapPath);
					})
				];
		}
	}
}

void FSimuEditorSlateModule::ImportFinish()
{
	TSharedPtr<SOverlay>Overlay;
	FSlateBrush* Image = FCoreStyle::Get().GetDefaultBrush();
	Image->ImageSize = FVector2D(740, 460);
	SAssignNew(WidgetSwitcher, SWidgetSwitcher);
	SAssignNew(Overlay, SOverlay)
		+ SOverlay::Slot()
		[
			SNew(SImage)
			.Image(Image)
		.Visibility(EVisibility::Hidden)
		]
	+ SOverlay::Slot()

		[
			WidgetSwitcher.ToSharedRef()
		];

	//WidgetSwitch 内容0
	WidgetSwitcher->AddSlot(0)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
		[
			SNew(SImage)
			.Image(FSimuEditorStyle::Get().GetBrush("SimuEditorSlate.xiangdao"))
		]
	+ SOverlay::Slot()
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
		.Padding(300, 40, 0, 0)
		.AutoHeight()
		[
			SNew(SFirstTextBlock)
			.TextContent(FText::FromString(L"向导已完成"))
		.TextSize(16)
		]
	+ SVerticalBox::Slot()
		.Padding(300, 50, 0, 0)
		.AutoHeight()
		[
			SNew(SFirstTextBlock)
			.TextContent(FText::FromString(L"一切准备就绪。"))
		]
	+ SVerticalBox::Slot()
		.Padding(300, 20, 0, 0)

		[
			SNew(SFirstTextBlock)
			.TextContent(FText::FromString(L"单击“完成”关闭向导，开始编辑应用。"))
		]
	+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		.HAlign(EHorizontalAlignment::HAlign_Left)
		.VAlign(EVerticalAlignment::VAlign_Bottom)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
		.Padding(620, 0, 0, 10)
		.AutoWidth()
		[
			SNew(SFirstButton)
			.Finish(true)
		.TextContent(FText::FromString(L"完  成"))
		.OnClickFinish_Lambda([&]() {
		FinishComplete->OnCompleted.Broadcast();
		FSlateApplication::Get().RequestDestroyWindow(FirstCustomDialog.ToSharedRef());
			})

		]
		]
		]
		];

	//弹出对话框
	SAssignNew(FirstCustomDialog, SFirstCustomDialog)
		.Title(FText::FromString(L"应用向导"))
		.UseScrollBox(false)
		.SizingRule(ESizingRule::FixedSize)
		.ClientSize(FVector2D(740, 460))
		.DialogContent(
			Overlay
		);
	FirstCustomDialog->ShowModal();



}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSimuEditorSlateModule, SimuEditorSlate)