#pragma once
#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

//������������
DECLARE_DELEGATE_OneParam(DelegateParam,const FString&);

class SAssociatedMapWidget :public SCompoundWidget
{

public:

	SLATE_BEGIN_ARGS(SAssociatedMapWidget)
	
	{

	}
	SLATE_ARGUMENT(FText, TextName)//�ļ�������
	SLATE_ARGUMENT(FText, TextTime)//�ļ����޸�ʱ��
	SLATE_ARGUMENT(FString, Path)//�ļ���·��
	SLATE_ARGUMENT(int32, TypeMap)//��ͼ����
	SLATE_EVENT(DelegateParam, OnClick)//�����¼�
	SLATE_END_ARGS()
	/**
	 * Construct this widget
	 *
	 * @param	InArgs	The declaration data for this widget
	 */
	void Construct(const FArguments& InArgs);

	FString Path;//�ļ�����Ӳ�̵�·��
	int32 TypeMap;//���ͣ�0ΪCode/UMG/App_   1ΪCarla
	FArguments Arguments;//��ʼ����

	FString GetAssetPath();//�������ͻ�ȡ��Ӧ���ʲ�·��
	//���嵥������
	DelegateParam ParamWidget;
	FReply ExecuteNoParamWidget();

};