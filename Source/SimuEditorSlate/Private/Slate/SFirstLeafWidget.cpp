#include "SFirstLeafWidget.h"

void SFirstLeafWidget::Construct(const FArguments& InArgs)
{
	Points.Add(InArgs._StartPoint.Get());
	Points.Add(InArgs._EndPoint.Get());
}

int32 SFirstLeafWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	FSlateDrawElement::MakeLines(OutDrawElements, LayerId, AllottedGeometry.ToPaintGeometry(), Points);
	return LayerId++;
}

FVector2D SFirstLeafWidget::ComputeDesiredSize(float) const
{
	return FVector2D(50,50);
}
