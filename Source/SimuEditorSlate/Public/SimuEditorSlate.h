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
	//通用Slate样式
	TSharedPtr<SScrollBox> ScrollBoxMap;
	TSharedPtr<SFirstCustomDialog> FirstCustomDialog;

	//关联地图功能区
	UConnectionMap* ConntectionMap;

	void AssociatedMap();
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void OnTextSearchMap(const FText& InText, ETextCommit::Type CommitInfo);
	

	//打开应用功能区
	UOpenTheApps* OpenTheApp;

	void OpenTheApps();
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void OnTextSearchOpenTheApp(const FText& InText, ETextCommit::Type CommitInfo);

	//应用向导功能区
	UApplication* Application;

	void Applications();
	TSharedPtr<SWidgetSwitcher> WidgetSwitcher;
	void SwidgetIndex(const bool NextIndex);
	//	1/2
	FString LoadMapName;
	void LoadMapNext(FString LoadMapNames);
	//新建地图名称
	TSharedPtr<SCheckBox> NewMapCheckBox;
	TSharedPtr<SHorizontalBox> NewMapHorizontalBox;
	TSharedPtr<SFirstTextBlock> NewMapFirstTextBlock;
	void OnTextNewMapChanged(const FText& InText);
	void OnCheckStateNewMap(ECheckBoxState InNewState);//勾选框触发事件
	void OnTextSearchNewMap(const FText& InText, ETextCommit::Type CommitInfo);//
	bool AllowNext;

	//关联已有地图
	TSharedPtr<SCheckBox> LoadMapCheckBox;
	TSharedPtr<SScrollBox> LoadMapSScrollBox;
	void FindAllLoadMap();
	void OnCheckStateLoadMap(ECheckBoxState InNewState);//勾选框触发事件


	//2/2
	//新建一个应用
	bool IsUINext ;
	FString UIName;
	TSharedPtr<SFirstTextBlock> UIFirstTextBlock;
	void UINext(FString UINames);
	void OnTextUIChanged(const FText & InText);
	void OnTextSearchUI(const FText& InText, ETextCommit::Type CommitInfo);


	//向导完成是否打开应用
	UFinishComplete* FinishComplete;
	void FinishWizard();

	FSimpleDelegate MyDelegate;
	FOnClicked MyOnClick;
	

	//初始UI
	UInitApps* InitTheApp;
	void InitApps();
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void OnTextSearchInitApps(const FText& InText, ETextCommit::Type CommitInfo);

	//导入素材成功或者失败
	void ImportFinish();


private:

};
