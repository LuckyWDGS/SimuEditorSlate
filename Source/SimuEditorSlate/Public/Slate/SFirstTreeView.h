#pragma once

#include "CoreMinimal.h"
#include "SFirstTreeView.generated.h"

UCLASS()
class UTreeItemData :public UObject {

	GENERATED_BODY()

public:
	FString MyName;
	float MyHeight=35.0;
	TArray<TSharedPtr<UTreeItemData>> Children;
};

class SFirstTreeView :public STreeView<TSharedPtr<UTreeItemData>>
{

public:
	void Construct(const FArguments& InArgs);

	TArray<TSharedPtr<UTreeItemData>> TreeItemDatas;

	TSharedRef<ITableRow> GenerateRowItem(TSharedPtr<UTreeItemData> InTreeItemData, const TSharedRef<STableViewBase>& OwnerTable);

	void GetChildrenForItem(TSharedPtr<UTreeItemData>InTreeItem, TArray<TSharedPtr<UTreeItemData>>& OutChildern);
};