#pragma once
#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

//声明单播代理
DECLARE_DELEGATE_OneParam(DelegateParam,const FString&);

class SAssociatedMapWidget :public SCompoundWidget
{

public:

	SLATE_BEGIN_ARGS(SAssociatedMapWidget)
	
	{

	}
	SLATE_ARGUMENT(FText, TextName)//文件夹名称
	SLATE_ARGUMENT(FText, TextTime)//文件夹修改时间
	SLATE_ARGUMENT(FString, Path)//文件夹路径
	SLATE_ARGUMENT(int32, TypeMap)//地图类型
	SLATE_EVENT(DelegateParam, OnClick)//单击事件
	SLATE_END_ARGS()
	/**
	 * Construct this widget
	 *
	 * @param	InArgs	The declaration data for this widget
	 */
	void Construct(const FArguments& InArgs);

	FString Path;//文件夹在硬盘的路径
	int32 TypeMap;//类型，0为Code/UMG/App_   1为Carla
	FArguments Arguments;//初始数据

	FString GetAssetPath();//根据类型获取对应的资产路径
	//定义单播代理
	DelegateParam ParamWidget;
	FReply ExecuteNoParamWidget();

};