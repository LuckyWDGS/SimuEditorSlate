// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "SimuEditorSlateType.generated.h"


/*������ͼ�Ľṹ��*/
USTRUCT(BlueprintType)
struct SIMUEDITORSLATE_API FSlateMapData
{
	GENERATED_USTRUCT_BODY()

	/*��ͼ����*/
	UPROPERTY(BlueprintReadWrite)
		FString MapName;

	/*��ͼ�޸�ʱ��*/
	UPROPERTY(BlueprintReadWrite)
		FString ModificationTime;

	/*�ļ���·��*/
	UPROPERTY(BlueprintReadWrite)
		FString DirectoryPath;

	/*��ͼ������*/
	UPROPERTY(BlueprintReadWrite)
		int32 TypeMap;

};