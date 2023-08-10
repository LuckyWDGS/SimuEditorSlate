// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "SimuEditorSlateType.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SimuEditorSlateBPF.generated.h"


UCLASS()
class  SIMUEDITORSLATE_API USimuEditorSlateBPF : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (CannotImplementInterfaceInBlueprint))
		static TArray<FSlateMapData> LoadMapToFind(FString FindDirectoryPath, FString Substring, bool NotContains, int32 TypeMap);

	UFUNCTION(BlueprintPure, meta = (CannotImplementInterfaceInBlueprint))
		static FString SelectedTime(int32 Param);

	UFUNCTION(BlueprintPure, meta = (CannotImplementInterfaceInBlueprint))
		static FString GetDataTime(FDateTime DateTime);


	
};
//关联地图异步节点
UCLASS()
class SIMUEDITORSLATE_API UConnectionMap : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOneStringResult, FString, NewConnetMaps);

public:
	UPROPERTY(BlueprintAssignable)
		FOneStringResult OnCompleted;

		UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", Category = "SimuEditorSlateBPF|Slate|关联地图"))
		static UConnectionMap* ConnectionMap(UObject* WorldContextObject){
			UConnectionMap* Node = NewObject<UConnectionMap>(WorldContextObject);
			return Node;
		}
		

protected:
	virtual void Activate();


};

//打开应用地图异步节点
UCLASS()
class SIMUEDITORSLATE_API UOpenTheApps : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

		DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOneStringResult, FString, NewFilePath);

public:
	UPROPERTY(BlueprintAssignable)
		FOneStringResult OnCompleted;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", Category = "SimuEditorSlateBPF|Slate|打开应用地图"))
		static UOpenTheApps* OpenTheApps(UObject* WorldContextObject) {
		UOpenTheApps* Node = NewObject<UOpenTheApps>(WorldContextObject);
		return Node;
	}


protected:
	virtual void Activate();


};

//应用向导异步节点
UCLASS()
class SIMUEDITORSLATE_API UApplication : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
		DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FThreeStringResult, bool ,NewMap,FString, ArtsMapName,FString, UIName);

public:
	UPROPERTY(BlueprintAssignable)
		FThreeStringResult OnCompleted;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", Category = "SimuEditorSlateBPF|Slate|应用向导"))
		static UApplication* Application(UObject* WorldContextObject) {
		UApplication* Node = NewObject<UApplication>(WorldContextObject);
		return Node;
	}


protected:
	virtual void Activate();


};

//结束应用向导异步节点
UCLASS()
class SIMUEDITORSLATE_API UFinishComplete : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FResult);

public:
	UPROPERTY(BlueprintAssignable)
		FResult OnCompleted;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", Category = "SimuEditorSlateBPF|Slate|应用向导完成"))
		static UFinishComplete* FinishWizared(UObject* WorldContextObject) {
		UFinishComplete* Node = NewObject<UFinishComplete>(WorldContextObject);
		return Node;
	}


protected:
	virtual void Activate();


};

//初始UI异步节点
UCLASS()
class SIMUEDITORSLATE_API UInitApps : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

		DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOneStringResult, FString, NewFilePath);

public:
	UPROPERTY(BlueprintAssignable)
		FOneStringResult OnCompleted;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", Category = "SimuEditorSlateBPF|Slate|打开应用地图"))
		static UInitApps* InitApps(UObject* WorldContextObject) {
		UInitApps* Node = NewObject<UInitApps>(WorldContextObject);
		return Node;
	}


protected:
	virtual void Activate();


};


//延迟异步节点
UCLASS()
class SIMUEDITORSLATE_API UDelay : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FResult);

public:
	UPROPERTY(BlueprintAssignable)
		FResult OnCompleted;
		float DelayTimer;
		FTimerHandle TimerHandle;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", Category = "SimuEditorSlateBPF|Slate|打开应用地图"))
		static UDelay* Delay(UObject* WorldContextObject,float DelayTime) {
		UDelay* Node = NewObject<UDelay>(WorldContextObject);
		Node->DelayTimer = DelayTime;
		return Node;
	}

	void DelayEvent();

protected:
	virtual void Activate();


};