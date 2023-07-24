#include "SFirstTreeView.h"

void SFirstTreeView::Construct(const FArguments& InArgs)
{
	FArguments Arguments = InArgs;
	////
	TSharedPtr<UTreeItemData> ZhangSan = MakeShareable(NewObject<UTreeItemData>());
	ZhangSan->MyName = FString("ZhangSan");
	TSharedPtr<UTreeItemData> ZhangSan1 = MakeShareable(NewObject<UTreeItemData>());
	ZhangSan1->MyName = FString("ZhangSan1");
	ZhangSan->Children.Add(ZhangSan1);

	TSharedPtr<UTreeItemData> LiSi = MakeShareable(NewObject<UTreeItemData>());
	LiSi->MyName = FString("LiSi");

	TSharedPtr<UTreeItemData> LiSi1 = MakeShareable(NewObject<UTreeItemData>());
	LiSi1->MyName = FString("LiSi1");
	TSharedPtr<UTreeItemData> LiSi2 = MakeShareable(NewObject<UTreeItemData>());
	LiSi2->MyName = FString("LiSi2");

	LiSi->Children.Add(LiSi1);
	LiSi->Children.Add(LiSi2);

	TreeItemDatas.Add(ZhangSan);
	TreeItemDatas.Add(LiSi);

	Arguments.TreeItemsSource(&TreeItemDatas);//数据源

	Arguments.OnGenerateRow_Raw(this, &SFirstTreeView::GenerateRowItem);

	Arguments.OnGetChildren_Raw(this, &SFirstTreeView::GetChildrenForItem);
	////

	STreeView::Construct(Arguments);

}




TSharedRef<ITableRow> SFirstTreeView::GenerateRowItem(TSharedPtr<UTreeItemData> InTreeItemData, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(STableRow<TSharedPtr<UTreeItemData>>, OwnerTable)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
		[
			SNew(STextBlock)
			.Text(FText::FromString(InTreeItemData->MyName))
		]
			+ SHorizontalBox::Slot()
		[
			SNew(STextBlock)
			.Text(FText::FromString(FString::SanitizeFloat(InTreeItemData->MyHeight)))
		]
			
		];
}

void SFirstTreeView::GetChildrenForItem(TSharedPtr<UTreeItemData>InTreeItem, TArray<TSharedPtr<UTreeItemData>>& OutChildern)
{
	OutChildern = InTreeItem->Children;

	//InTreeItem->Map InTreeItem->Children.Valuse;
}