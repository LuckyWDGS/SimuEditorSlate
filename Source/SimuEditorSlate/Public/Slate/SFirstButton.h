#pragma once

#include "Widgets/SCompoundWidget.h"
//������������
DECLARE_DELEGATE(DelegateClick);
//������������
DECLARE_DELEGATE_OneParam(DelegateNext,const bool);
class SFirstButton :public SCompoundWidget
{

public:
	SLATE_BEGIN_ARGS(SFirstButton)
		:_Next(true)
		,_Finish(false)
	{

	}
		SLATE_ARGUMENT(FText, TextContent)//��ť����
		SLATE_ARGUMENT(bool, Next)//�Ƿ�Ϊ��һ��
		SLATE_ARGUMENT(bool, Finish)//�Ƿ����
		SLATE_EVENT(DelegateClick, OnClickFinish)//�����¼�
		SLATE_EVENT(DelegateNext, OnClickNext)//�����¼�
		SLATE_END_ARGS()
	/**
	 * Construct this widget
	 *
	 * @param	InArgs	The declaration data for this widget
	 */
	void Construct(const FArguments& InArgs);
	FArguments Arguments;//��ʼ����
	bool IsNext;//�Ƿ�Ϊ��һ��
	bool IsFinish;//�Ƿ����
	DelegateClick OnClicked;
	DelegateClick ClickFinish;
	DelegateNext  ClickNext;
		 
	FReply OnClick();
};