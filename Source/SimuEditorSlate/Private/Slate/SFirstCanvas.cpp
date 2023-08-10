#include "SFirstCanvas.h"
#include "SFirstTreeView.h"
#include "SFirstListView.h"
#include "Widgets/Layout/SGridPanel.h"
#include "Widgets/Views/STreeView.h"


void SFirstCanvas::Construct(const FArguments& InArgs)
{
	SCanvas::Construct(InArgs);
	
	AddSlot()
		.Position(FVector2D(100, 100))
		.Size(FVector2D(100, 40))
		[
			SNew(SButton)
			.OnClicked(FOnClicked::CreateRaw(this, &SFirstCanvas::teste))
		];
	AddSlot()
		.Position(FVector2D(300, 100))
		.Size(FVector2D(100, 40))
		[
			SNew(SButton)
			.OnClicked(FOnClicked::CreateRaw(this, &SFirstCanvas::teste2))
		];

	
	Options.Add(MakeShareable(new FString("1")));
	Options.Add(MakeShareable(new FString("2")));
	Options.Add(MakeShareable(new FString("3")));
	Options.Add(MakeShareable(new FString("4")));
	AddSlot()
		.Position(FVector2D(500, 100))
		.Size(FVector2D(100, 40))
		[
			SNew(SComboBox<TSharedPtr<FString>>)
	
			.OptionsSource(&Options)
			.OnGenerateWidget_Lambda([](TSharedPtr<FString> InValue){
			return SNew(STextBlock).Text(FText::FromString(*InValue));
			})
			.OnSelectionChanged_Lambda([this](TSharedPtr<FString>NewOption,ESelectInfo::Type SelectType) {
				CurrentSelected = Options.Find(NewOption);
				FString in = NewOption.ToSharedRef().Get();
				SFirstCanvas::teste3(in);
			})

			[
				SNew(STextBlock).Text_Lambda([this]() {
				if (CurrentSelected<0 || CurrentSelected>Options.Num() - 1)
					return FText::FromString("");
				else
					return FText::FromString(*Options[CurrentSelected]);

					})
			]
		];
		//添加水平布局
	AddSlot()//添加一个槽
		.Position(FVector2D(100, 300))
		.Size(FVector2D(400, 80))
		[
			SNew(SHorizontalBox)
	+ SHorizontalBox::Slot()
		.FillWidth(2.0f)
		[
			SNew(SButton)
		]
	+ SHorizontalBox::Slot()
		[
			SNew(SButton)
		]
	+ SHorizontalBox::Slot()
		[
			SNew(SButton)
		]
		];

	//添加垂直布局
	AddSlot()//添加一个槽
		.Position(FVector2D(100, 500))
		.Size(FVector2D(100, 400))
		[
			SNew(SVerticalBox)
	+ SVerticalBox::Slot()
		[
			SNew(SButton)
		]
	+ SVerticalBox::Slot()
		[
			SNew(SButton)
		]
	+ SVerticalBox::Slot()
		[
			SNew(SButton)
		]
		];

	//添加树视图
	AddSlot()//添加一个槽
		.Position(FVector2D(600, 100))
		.Size(FVector2D(300, 400))
		[
			SNew(SFirstTreeView)
		];

	//添加列表视图
	AddSlot()//添加一个槽
		.Position(FVector2D(600, 200))
		.Size(FVector2D(300, 400))
		[
			SNew(SFirstListView)
		];
	//添加图像
	AddSlot()//添加一个槽
		.Position(FVector2D(400, 200))
		.Size(FVector2D(200, 200))
		[
			SNew(SImage)
			.Image(FCoreStyle::Get().GetBrush("TrashCan"))
		];

	//添加网格布局
	AddSlot()//添加一个槽
		.Position(FVector2D(400, 500))
		.Size(FVector2D(200, 200))
		[
			SNew(SGridPanel)
			.FillColumn(0,1)
			.FillColumn(1,1)
			.FillRow(0,1)
			.FillRow(1,1)
			+SGridPanel::Slot(0,0)
		[
			SNew(SImage)
			.Image(FCoreStyle::Get().GetBrush("TrashCan"))
		]
			+ SGridPanel::Slot(0, 1)
		[
					SNew(SImage)
					.Image(FCoreStyle::Get().GetBrush("TrashCan"))
		]
			+ SGridPanel::Slot(1, 0)
		[
					SNew(SImage)
					.Image(FCoreStyle::Get().GetBrush("TrashCan"))
		]
			+ SGridPanel::Slot(1, 1)
		[
					SNew(SImage)
					.Image(FCoreStyle::Get().GetBrush("TrashCan"))
		]
		];

}

FReply SFirstCanvas::teste()
{
	FMessageDialog::Open(EAppMsgType::OkCancel, FText::FromString("叫爸爸"));
	return FReply::Handled();
}

FReply SFirstCanvas::teste2()
{
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("叫啥？？"));
	return FReply::Handled();
}

FReply SFirstCanvas::teste3(FString In)
{

	return FReply::Handled();

}


