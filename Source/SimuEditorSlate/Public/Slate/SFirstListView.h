#pragma once

#include "CoreMinimal.h"
#include "SFirstListView.generated.h"

UCLASS()
class UListViewItemData : public UObject 
{

	GENERATED_BODY()

public:
	FString MyName= "ZhangSan";
};

class SFirstListView :public SListView<TSharedPtr<UListViewItemData>>
{
public:
	void Construct(const FArguments& InArgs);

	TSharedRef<ITableRow> GenerateRowItem(TSharedPtr<UListViewItemData> InListItemData, const TSharedRef<STableViewBase>& OwnerTable);


	TArray<TSharedPtr<UListViewItemData>>ListItemData;
};