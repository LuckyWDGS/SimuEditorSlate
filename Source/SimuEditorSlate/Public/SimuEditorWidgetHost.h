//// Copyright Kite & Lightning
//
//#pragma once
//
//#include "UObject/Class.h"
//#include "Components/NativeWidgetHost.h"
//#include "SimuEditorWidgetHost.generated.h"
//
//
//
//USTRUCT(BlueprintType)
//struct SIMUEDITORSLATE_API FSimuSWidgetWrapper
//{
//	GENERATED_USTRUCT_BODY()
//
//		TSharedPtr<SWidget> Widget;
//};
//
//template<>
//struct TStructOpsTypeTraits<FSimuSWidgetWrapper> : public TStructOpsTypeTraitsBase2<FSimuSWidgetWrapper>
//{
//	enum
//	{
//		WithCopy = true,
//	};
//};
//
///**
// *添加UMG控制板小标签继承自UNativeWidgetHost
// */
//UCLASS()
//class SIMUEDITORSLATE_API USimuEditorWidgetHost : public UNativeWidgetHost
//{
//	GENERATED_BODY()
//
//
//		USimuEditorWidgetHost(const FObjectInitializer& ObjectInitializer);
//
//#if WITH_EDITOR
//	//获取调色板类别
//	virtual const FText GetPaletteCategory() override;
//#endif
//
//};
//
