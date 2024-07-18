// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/MapMenu/MapWidget.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Styling/SlateColor.h"

#include "MedievalDynasty/Player/InteractionMenu/MapMenu/MapMenuWidget.h"

void UMapWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void UMapWidget::UpdateWaypointsOnMap()
{
	if (!IsValid(MapMenuWidget))
		return;

	const TArray<FWaypointSort> SortedWaypointsToCategory = MapMenuWidget->GetSortedWaypointsToCategory();
	const int32& CurrentWaypointsOnMapIndex = MapMenuWidget->GetCurrentWaypointsOnMapIndex();

	if (CurrentWaypointsOnMapIndex >= SortedWaypointsToCategory.Num() || CurrentWaypointsOnMapIndex < 0)
		return;

	DeleteWaypointsFromMap();

	for (const FWaypointOnMap& CurrentWaypoint : SortedWaypointsToCategory[CurrentWaypointsOnMapIndex].AllSortedWaypoints)
	{
		TObjectPtr<UImage> AddedWaypointImage = NewObject<UImage>(MapCanvasPanel);
		if (!IsValid(AddedWaypointImage))
			continue;

		AddedWaypointImage->SetBrush(CurrentWaypoint.WaypointIconImageBrush);

		TObjectPtr<UCanvasPanelSlot> AddedWaypointImageCanvasSlot = MapCanvasPanel->AddChildToCanvas(AddedWaypointImage);

		if (!IsValid(AddedWaypointImageCanvasSlot))
			continue;
		
		UpdateWaypointTransform(AddedWaypointImageCanvasSlot, CurrentWaypoint);
		AddedWaypointImageCanvasSlot->SetAutoSize(true);

		AddedWaypointImageCanvasSlot->SetAlignment(FVector2D(0.5f));
		AddedWaypointImageCanvasSlot->SetAnchors(FAnchors(0.5f, 0.5f));
		AddedWaypointImageCanvasSlot->SetZOrder(1);

		AddedWaypointImage->SetRenderScale(SavedWaypointRenderScale);

		CurrentWaypointsOnMapImages.Add(AddedWaypointImage);

		if (CurrentWaypoint.bTrackLocation)
		{
			WaypointsToUpdateInRealTime.Add(AddedWaypointImageCanvasSlot, CurrentWaypoint);
		}
	}

	if (WaypointsToUpdateInRealTime.Num() == 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(UpdateWaypointsHandle);
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(UpdateWaypointsHandle, this, &UMapWidget::UpdateWaypointsInRealTime, UpdateWaypointsTime, true);
}

void UMapWidget::DeleteWaypointsFromMap()
{
	for (TObjectPtr<UImage> CurrentWaypointImage : CurrentWaypointsOnMapImages)
	{
		MapCanvasPanel->RemoveChild(CurrentWaypointImage);
	}

	WaypointsToUpdateInRealTime.Empty();
	CurrentWaypointsOnMapImages.Empty();
}

void UMapWidget::UpdateWaypointsInRealTime()
{
	if (WaypointsToUpdateInRealTime.Num() == 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(UpdateWaypointsHandle);
		return;
	}

	for (TPair<TObjectPtr<UCanvasPanelSlot>, FWaypointOnMap>& CurrentPair : WaypointsToUpdateInRealTime)
	{
		if (!IsValid(CurrentPair.Key))
			continue;

		UpdateWaypointTransform(CurrentPair.Key, CurrentPair.Value);
	}
}

void UMapWidget::UpdateWaypointTransform(TObjectPtr<class UCanvasPanelSlot> WaypointCanvasPanel, const FWaypointOnMap& WaypointOnMap)
{
	if (!IsValid(WaypointCanvasPanel))
		return;

	FTransform NewTransform = FTransform(WaypointOnMap.WaypointWorldLocation);
	if (WaypointOnMap.bCustomTransformFunction && WaypointOnMap.GetOwnerTransform)
	{
		NewTransform = WaypointOnMap.GetOwnerTransform();
	}
	else if (IsValid(WaypointOnMap.ActorToTrack))
	{
		NewTransform = WaypointOnMap.ActorToTrack->GetActorTransform();
	}

	WaypointCanvasPanel->SetPosition(TransformWorldLocationToMap(NewTransform.GetLocation()));

	if (WaypointOnMap.bTrackRotation)
		WaypointCanvasPanel->Content->SetRenderTransformAngle(NewTransform.Rotator().Yaw);
}

FVector2D UMapWidget::TransformWorldLocationToMap(const FVector& VectorToTransform)
{
	FVector2D NewPosition = FVector2D(VectorToTransform / WorldLocationToMapDivider);
	NewPosition.X = -NewPosition.X;
	Swap(NewPosition.X, NewPosition.Y);

	return NewPosition;
}

#pragma region ////////////// MOVE/ZOOM Map ////////////
FReply UMapWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseMove(InGeometry, InMouseEvent);

	if (!bIsDraggingMap)
		return FReply::Handled();

	const FVector2D NewTranslation = MapCanvasPanel->GetRenderTransform().Translation + (InMouseEvent.GetCursorDelta() * DraggingSpeed);
	MapCanvasPanel->SetRenderTranslation(ClampSides(InGeometry, NewTranslation));

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
	CalculatedTranslation = (CalculatedTranslation - MapCanvasPanel->GetRenderTransform().Translation) * (ZoomMultiplier - 1.f);

	const FVector2D ClampedTranslation = ClampSides(InGeometry, MapCanvasPanel->GetRenderTransform().Translation - CalculatedTranslation);
	MapCanvasPanel->SetRenderTranslation(ClampedTranslation);

	const FVector2D NewScale = MapCanvasPanel->GetRenderTransform().Scale * ZoomMultiplier;
	MapCanvasPanel->SetRenderScale(NewScale);

	ScaleWaypoints(ZoomMultiplier);

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

FVector2D UMapWidget::ClampSides(const FGeometry& MyGeometry, FVector2D VectorToClamp)
{
	// Calculate the size of the area that is not visible on the map.
	FVector2D NotVisibleAreaSize = (MapImage->GetDesiredSize() * MapCanvasPanel->GetRenderTransform().Scale) - MyGeometry.GetLocalSize();

	// dividing the NotVisibleAreaSize into two parts (Left/Top and Right/Bottom sides).
	const float TwoSides = 2.f;
	NotVisibleAreaSize /= TwoSides;

	return FVector2D(FMath::Clamp(VectorToClamp.X, NotVisibleAreaSize.X * -1.f, NotVisibleAreaSize.X),
		FMath::Clamp(VectorToClamp.Y, NotVisibleAreaSize.Y * -1.f, NotVisibleAreaSize.Y));
}

void UMapWidget::ScaleWaypoints(float ZoomMultiplier)
{
	for (TObjectPtr<UImage> CurrentWaypointImage : CurrentWaypointsOnMapImages)
	{
		if (!IsValid(CurrentWaypointImage))
			return;

		SavedWaypointRenderScale = CurrentWaypointImage->GetRenderTransform().Scale / ZoomMultiplier;
		CurrentWaypointImage->SetRenderScale(SavedWaypointRenderScale);
	}
}
#pragma endregion

