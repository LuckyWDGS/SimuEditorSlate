// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Slate/SFirstCustomDialog.h"
#include "Slate/SFirstTextBlock.h"

#include "SimuEditorSlateBPF.h"
#include "SimuEditorSlateType.h"

class FToolBarBuilder;
class FMenuBuilder;

class FSimuEditorSlateModule : public IModuleInterface
{
public:



	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	//ͨ��Slate��ʽ
	TSharedPtr<SScrollBox> ScrollBoxMap;
	TSharedPtr<SFirstCustomDialog> FirstCustomDialog;

	//������ͼ������
	UConnectionMap* ConntectionMap;

	void AssociatedMap();
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void OnTextSearchMap(const FText& InText, ETextCommit::Type CommitInfo);
	

	//��Ӧ�ù�����
	UOpenTheApps* OpenTheApp;

	void OpenTheApps();
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void OnTextSearchOpenTheApp(const FText& InText, ETextCommit::Type CommitInfo);

	//Ӧ���򵼹�����
	UApplication* Application;

	void Applications();
	TSharedPtr<SWidgetSwitcher> WidgetSwitcher;
	void SwidgetIndex(const bool NextIndex);
	//	1/2
	FString LoadMapName;
	void LoadMapNext(FString LoadMapNames);
	//�½���ͼ����
	TSharedPtr<SCheckBox> NewMapCheckBox;
	TSharedPtr<SHorizontalBox> NewMapHorizontalBox;
	TSharedPtr<SFirstTextBlock> NewMapFirstTextBlock;
	void OnTextNewMapChanged(const FText& InText);
	void OnCheckStateNewMap(ECheckBoxState InNewState);//��ѡ�򴥷��¼�
	void OnTextSearchNewMap(const FText& InText, ETextCommit::Type CommitInfo);//
	bool AllowNext;

	//�������е�ͼ
	TSharedPtr<SCheckBox> LoadMapCheckBox;
	TSharedPtr<SScrollBox> LoadMapSScrollBox;
	void FindAllLoadMap();
	void OnCheckStateLoadMap(ECheckBoxState InNewState);//��ѡ�򴥷��¼�


	//2/2
	//�½�һ��Ӧ��
	bool IsUINext ;
	FString UIName;
	TSharedPtr<SFirstTextBlock> UIFirstTextBlock;
	void UINext(FString UINames);
	void OnTextUIChanged(const FText & InText);
	void OnTextSearchUI(const FText& InText, ETextCommit::Type CommitInfo);


	//������Ƿ��Ӧ��
	UFinishComplete* FinishComplete;
	void FinishWizard();

	FSimpleDelegate MyDelegate;
	FOnClicked MyOnClick;
	

	//��ʼUI
	UInitApps* InitTheApp;
	void InitApps();
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void OnTextSearchInitApps(const FText& InText, ETextCommit::Type CommitInfo);

	//�����زĳɹ�����ʧ��
	void ImportFinish();


private:

};
