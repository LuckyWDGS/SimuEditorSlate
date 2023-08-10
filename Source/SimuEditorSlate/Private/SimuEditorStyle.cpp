// Copyright 2022 Xinin Zeng (DreamingPoet). All Rights Reserved.

#include "SimuEditorStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"

TSharedPtr< FSlateStyleSet > FSimuEditorStyle::StyleInstance = NULL;

void FSimuEditorStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FSimuEditorStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FSimuEditorStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("SimuEditorStyle"));
	return StyleSetName;
}

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".ttf") ), __VA_ARGS__ )
#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".otf") ), __VA_ARGS__ )

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon22x22(22.0f, 22.0f);
const FVector2D Icon24x24(24.0f, 24.0f);
const FVector2D Icon32x32(32.0f, 32.0f);
const FVector2D Icon40x40(40.0f, 40.0f);
const FVector2D Icon64x64(64.0f, 64.0f);
const FVector2D Icon128x128(128.0f, 128.0f);

const FLinearColor TintHui(0.1912, 0.1912, 0.1912, 1);

TSharedRef< FSlateStyleSet > FSimuEditorStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("SimuEditorStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("SimuEditorSlate")->GetBaseDir() / TEXT("Resources"));

	Style->Set("SimuEditorSlate.Button", new IMAGE_BRUSH(TEXT("Button_32x"), Icon32x32));
	Style->Set("SimuEditorSlate.White1x", new IMAGE_BRUSH(TEXT("White_1x"), FVector2D(1, 2)));
	Style->Set("SimuEditorSlate.xiangdao", new IMAGE_BRUSH(TEXT("xiangdao"), FVector2D(740, 460)));
	Style->Set("SimuEditorSlate.MapEditableTextBox", new IMAGE_BRUSH(TEXT("MapEditableTextBox"), Icon22x22));
	Style->Set("SimuEditorSlate.MapEditableTextBoxH", new IMAGE_BRUSH(TEXT("MapEditableTextBoxH"), Icon22x22));
	//菜单栏图标
	Style->Set("SimuEditorSlate.AddAlgorithm", new IMAGE_BRUSH(TEXT("添加算法"), Icon40x40, TintHui));
	Style->Set("SimuEditorSlate.AssociatedMap", new IMAGE_BRUSH(TEXT("更换关联"), Icon40x40, TintHui));
	Style->Set("SimuEditorSlate.BrowseLibrary", new IMAGE_BRUSH(TEXT("浏览素材库"), Icon40x40, TintHui));
	Style->Set("SimuEditorSlate.ExportApplication", new IMAGE_BRUSH(TEXT("导出应用"), Icon40x40, TintHui));
	Style->Set("SimuEditorSlate.ImportMaterial", new IMAGE_BRUSH(TEXT("导入素材"), Icon40x40, TintHui));
	Style->Set("SimuEditorSlate.NewApplication", new IMAGE_BRUSH(TEXT("新建应用"), Icon40x40, TintHui));
	Style->Set("SimuEditorSlate.OpenApplication", new IMAGE_BRUSH(TEXT("打开应用"), Icon40x40, TintHui));
	Style->Set("SimuEditorSlate.OpenUIEditor", new IMAGE_BRUSH(TEXT("打开UI编辑"), Icon40x40, TintHui));
	



	//地图搜索栏样式
	FEditableTextBoxStyle MapEditableTextBox;
	MapEditableTextBox.ForegroundColor=FLinearColor(1, 1, 1, 1);

	MapEditableTextBox.BackgroundImageNormal = *Style->GetBrush("SimuEditorSlate.MapEditableTextBox");
	MapEditableTextBox.BackgroundImageNormal.DrawAs = ESlateBrushDrawType::Box;
	MapEditableTextBox.BackgroundImageNormal.Margin = 0.25;

	MapEditableTextBox.BackgroundImageHovered = *Style->GetBrush("SimuEditorSlate.MapEditableTextBoxH");
	MapEditableTextBox.BackgroundImageHovered.DrawAs = ESlateBrushDrawType::Box;
	MapEditableTextBox.BackgroundImageHovered.Margin = 0.25;

	MapEditableTextBox.BackgroundImageFocused = *Style->GetBrush("SimuEditorSlate.MapEditableTextBoxH");
	MapEditableTextBox.BackgroundImageFocused.DrawAs = ESlateBrushDrawType::Box;
	MapEditableTextBox.BackgroundImageFocused.Margin = 0.25;
	Style->Set("SimuEditorSlate.MapEditableTextBox", MapEditableTextBox);

	//地图滚动框样式
	FScrollBoxStyle MapScrollBoxStyle;
	MapScrollBoxStyle.TopShadowBrush.ImageSize = FVector2D(16, 4);
	MapScrollBoxStyle.TopShadowBrush.TintColor = FLinearColor(0, 0, 0, 0.3);
	MapScrollBoxStyle.TopShadowBrush.DrawAs = ESlateBrushDrawType::Box;
	MapScrollBoxStyle.TopShadowBrush.Margin = FMargin(0.5, 1, 0.5, 0.0);

	MapScrollBoxStyle.BottomShadowBrush.ImageSize = FVector2D(16, 4);
	MapScrollBoxStyle.BottomShadowBrush.TintColor = FLinearColor(0, 0, 0, 0.3);
	MapScrollBoxStyle.BottomShadowBrush.DrawAs = ESlateBrushDrawType::Box;
	MapScrollBoxStyle.BottomShadowBrush.Margin = FMargin(0.5, 0, 0.5, 1.0);
	Style->Set("SimuEditorSlate.MapScrollBoxStyle", MapScrollBoxStyle);

	//地图滚动条样式
	FScrollBarStyle MapScrollBarStyle;
	MapScrollBarStyle.NormalThumbImage.TintColor = FLinearColor(0.021219, 0.021219, 0.021219, 1);
	MapScrollBarStyle.NormalThumbImage.DrawAs = ESlateBrushDrawType::Box;
	MapScrollBarStyle.NormalThumbImage.Margin = 0.25;

	MapScrollBarStyle.HoveredThumbImage.TintColor = FLinearColor(0.029997, 0.029997, 0.029997, 1);
	MapScrollBarStyle.HoveredThumbImage.DrawAs = ESlateBrushDrawType::Box;
	MapScrollBarStyle.HoveredThumbImage.Margin = 0.25;

	MapScrollBarStyle.DraggedThumbImage.TintColor = FLinearColor(0.021219, 0.021219, 0.021219, 1);
	MapScrollBarStyle.DraggedThumbImage.DrawAs = ESlateBrushDrawType::Box;
	MapScrollBarStyle.DraggedThumbImage.Margin = 0.25;
	Style->Set("SimuEditorSlate.MapScrollBarStyle", MapScrollBarStyle);


	// 地图选择按钮
	FButtonStyle MapButtonStyle;
	MapButtonStyle.Normal = *Style->GetBrush("SimuEditorSlate.White1x");
	MapButtonStyle.Normal.DrawAs = ESlateBrushDrawType::Image;
	MapButtonStyle.Normal.TintColor = FLinearColor(1, 1, 1, 0);
	MapButtonStyle.Hovered = *Style->GetBrush("SimuEditorSlate.White1x");
	MapButtonStyle.Hovered.DrawAs = ESlateBrushDrawType::Image;
	MapButtonStyle.Hovered.TintColor = FLinearColor(0.06301, 0.168269, 0.304987,1);
	MapButtonStyle.Pressed = *Style->GetBrush("SimuEditorSlate.White1x");
	MapButtonStyle.Pressed.DrawAs = ESlateBrushDrawType::Image;
	MapButtonStyle.Pressed.TintColor = FLinearColor(0.11792, 0.222952, 0.359375, 1);
	Style->Set("SimuEditorSlate.MapButton", MapButtonStyle);


	// 向导通用按钮
	FButtonStyle ApplicationButtonStyle;
	ApplicationButtonStyle.Normal = *Style->GetBrush("SimuEditorSlate.MapEditableTextBox");
	ApplicationButtonStyle.Normal.ImageSize = FVector2D(80, 22);
	ApplicationButtonStyle.Normal.DrawAs = ESlateBrushDrawType::Box;
	ApplicationButtonStyle.Normal.Margin = 0.25;

	ApplicationButtonStyle.Hovered = *Style->GetBrush("SimuEditorSlate.MapEditableTextBoxH");
	ApplicationButtonStyle.Hovered.ImageSize = FVector2D(22, 22);
	ApplicationButtonStyle.Hovered.DrawAs = ESlateBrushDrawType::Box;
	ApplicationButtonStyle.Hovered.Margin = 0.25;

	ApplicationButtonStyle.Pressed = *Style->GetBrush("SimuEditorSlate.MapEditableTextBox");
	ApplicationButtonStyle.Pressed.ImageSize = FVector2D(22, 22);
	ApplicationButtonStyle.Pressed.TintColor = FLinearColor(0.442708, 0.442708, 0.442708, 1);
	ApplicationButtonStyle.Pressed.DrawAs = ESlateBrushDrawType::Box;
	ApplicationButtonStyle.Pressed.Margin = 0.25;
	Style->Set("SimuEditorSlate.ApplicationButtonStyle", ApplicationButtonStyle);



	return Style;
}

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef TTF_FONT
#undef OTF_FONT

void FSimuEditorStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FSimuEditorStyle::Get()
{
	return *StyleInstance;
}
