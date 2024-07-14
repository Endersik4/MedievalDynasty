// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/MapMenu/MapWidget.h"
#include "Components/Image.h"

void UMapWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

FReply UMapWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseMove(InGeometry, InMouseEvent);

	if (!bIsDraggingMap)
		return FReply::Handled();

	const FVector2D NewTranslation = MapImage->GetRenderTransform().Translation + (InMouseEvent.GetCursorDelta() * DraggingSpeed);
	MapImage->SetRenderTranslation(ClampSides(InGeometry, NewTranslation));

	return FReply::Handled();
}

FReply UMapWidget::NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseWheel(InGeometry, InMouseEvent);

	if (InMouseEvent.GetWheelDelta() > 0.f && CurrentZoom < ZoomRange.GetUpperBoundValue())
	{
		CurrentZoom++;
	}
	else if (InMouseEvent.GetWheelDelta() < 0.f && CurrentZoom > ZoomRange.GetLowerBoundValue())
	{
		CurrentZoom--;
	}
	else
		return FReply::Handled();

	FVector2D CalculatedTranslation = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition()) - (InGeometry.GetLocalSize() / 2.f);
	float ZoomMultiplier = InMouseEvent.GetWheelDelta() > 0.f ? 1.f / ZoomFactor : ZoomFactor;
	CalculatedTranslation = (CalculatedTranslation - MapImage->GetRenderTransform().Translation) * (ZoomMultiplier - 1.f);

	const FVector2D ClampedTranslation = ClampSides(InGeometry, MapImage->GetRenderTransform().Translation - CalculatedTranslation);
	MapImage->SetRenderTranslation(ClampedTranslation);

	const FVector2D NewScale = MapImage->GetRenderTransform().Scale * ZoomMultiplier;
	MapImage->SetRenderScale(NewScale);

	return FReply::Handled();
}

FReply UMapWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	bIsDraggingMap = !(InMouseEvent.GetEffectingButton() == MouseButtonForDraggingMap);

	return (bIsDraggingMap ? FReply::Unhandled() : FReply::Handled());
}

FReply UMapWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	bIsDraggingMap = InMouseEvent.GetEffectingButton() == MouseButtonForDraggingMap;

	return (bIsDraggingMap ? FReply::Handled() : FReply::Unhandled());
}

void UMapWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	bIsDraggingMap = false;
}

FVector2D UMapWidget::ClampSides(const FGeometry& MyGeometry, FVector2D VectorToClamp)
{
	// Calculate the size of the area that is not visible on the map.
	FVector2D NotVisibleAreaSize = (MapImage->GetDesiredSize() * MapImage->GetRenderTransform().Scale) - MyGeometry.GetLocalSize();

	// dividing the NotVisibleAreaSize into two parts (Left/Top and Right/Bottom sides).
	const float TwoSides = 2.f;
	NotVisibleAreaSize /= TwoSides;

	return FVector2D(FMath::Clamp(VectorToClamp.X, NotVisibleAreaSize.X * -1.f, NotVisibleAreaSize.X),
		FMath::Clamp(VectorToClamp.Y, NotVisibleAreaSize.Y * -1.f, NotVisibleAreaSize.Y));
}

