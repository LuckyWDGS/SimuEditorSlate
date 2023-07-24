#include "SFirstListView.h"

void SFirstListView::Construct(const FArguments& InArgs)
{
	FArguments Argument = InArgs;
	ListItemData.Add(MakeShareable(NewObject<UListViewItemData>()));
	ListItemData.Add(MakeShareable(NewObject<UListViewItemData>()));
	ListItemData.Add(MakeShareable(NewObject<UListViewItemData>()));


	Argument.ListItemsSource(&ListItemData);
	Argument.OnGenerateRow_Raw(this, &SFirstListView::GenerateRowItem);



	SListView::Construct(Argument);
}

TSharedRef<ITableRow> SFirstListView::GenerateRowItem(TSharedPtr<UListViewItemData> InListItemData, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(STableRow<TSharedPtr<UListViewItemData>>, OwnerTable)
		[
			SNew(STextBlock)
			.Text(FText::FromString(InListItemData->MyName))
		];
}
