#pragma once

#include "CoreMinimal.h"
#include "Widgets/SLeafWidget.h"

class SFirstLeafWidget :public SLeafWidget
{

public:
	SLATE_BEGIN_ARGS(SFirstLeafWidget)
		:_StartPoint(FVector2D(0,0))
		,_EndPoint(FVector2D(0,0))

	{

	}
	SLATE_ATTRIBUTE(FVector2D,StartPoint)
	SLATE_ATTRIBUTE(FVector2D,EndPoint)
	SLATE_END_ARGS()

		void Construct(const FArguments& InArgs);

	// Begin SWidget overrides

		/**
		 * Overwritten from SWidget.
		 *
		 * LeafWidgets provide a visual representation of themselves. They do so by adding DrawElement(s)
		 * to the OutDrawElements. DrawElements should have their positions set to absolute coordinates in
		 * Window space; for this purpose the Slate system provides the AllottedGeometry parameter.
		 * AllottedGeometry describes the space allocated for the visualization of this widget.
		 *
		 * Whenever possible, LeafWidgets should avoid dealing with layout properties. See TextBlock for an example.
		 */
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	/**
	 * Overwritten from SWidget.
	 *
	 * LeafWidgets should compute their DesiredSize based solely on their visual representation. There is no need to
	 * take child widgets into account as LeafWidgets have none by definition. For example, the TextBlock widget simply
	 * measures the area necessary to display its text with the given font and font size.
	 */
	virtual FVector2D ComputeDesiredSize(float) const override ;

	TArray<FVector2D>Points;
};