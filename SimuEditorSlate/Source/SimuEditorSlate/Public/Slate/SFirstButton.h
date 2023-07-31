#pragma once

#include "Widgets/SCompoundWidget.h"
//声明单播代理
DECLARE_DELEGATE(DelegateClick);
//声明单播代理
DECLARE_DELEGATE_OneParam(DelegateNext,const bool);
class SFirstButton :public SCompoundWidget
{

public:
	SLATE_BEGIN_ARGS(SFirstButton)
		:_Next(true)
		,_Finish(false)
	{

	}
		SLATE_ARGUMENT(FText, TextContent)//按钮内容
		SLATE_ARGUMENT(bool, Next)//是否为下一步
		SLATE_ARGUMENT(bool, Finish)//是否完成
		SLATE_EVENT(DelegateClick, OnClickFinish)//单击事件
		SLATE_EVENT(DelegateNext, OnClickNext)//单击事件
		SLATE_END_ARGS()
	/**
	 * Construct this widget
	 *
	 * @param	InArgs	The declaration data for this widget
	 */
	void Construct(const FArguments& InArgs);
	FArguments Arguments;//初始数据
	bool IsNext;//是否为下一步
	bool IsFinish;//是否完成
	DelegateClick OnClicked;
	DelegateClick ClickFinish;
	DelegateNext  ClickNext;
		 
	FReply OnClick();
};