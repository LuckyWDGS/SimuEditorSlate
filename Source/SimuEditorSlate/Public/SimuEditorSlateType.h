// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "SimuEditorSlateType.generated.h"


/*关联地图的结构体*/
USTRUCT(BlueprintType)
struct SIMUEDITORSLATE_API FSlateMapData
{
	GENERATED_USTRUCT_BODY()

	/*地图名称*/
	UPROPERTY(BlueprintReadWrite)
		FString MapName;

	/*地图修改时间*/
	UPROPERTY(BlueprintReadWrite)
		FString ModificationTime;

	/*文件夹路径*/
	UPROPERTY(BlueprintReadWrite)
		FString DirectoryPath;

	/*地图、类型*/
	UPROPERTY(BlueprintReadWrite)
		int32 TypeMap;

};