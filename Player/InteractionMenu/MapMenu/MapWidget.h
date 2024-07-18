// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WaypointData.h"
#include "MapWidget.generated.h"

UCLASS()
class MEDIEVALDYNASTY_API UMapWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetMapMenuWidget(TObjectPtr<class UMapMenuWidget> NewMapMenuWidget) { MapMenuWidget = NewMapMenuWidget; }
	
	void UpdateWaypointsOnMap();

protected:
	virtual void NativeOnInitialized() override;

	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> MapCanvasPanel = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UImage> MapImage = nullptr;

private:
	UPROPERTY(EditAnywhere, Category = "Map Settings")
	FKey MouseButtonForDraggingMap = FKey();
	UPROPERTY(EditAnywhere, Category = "Map Settings")
	float DraggingSpeed = 1.f;
	UPROPERTY(EditAnywhere, Category = "Map Settings")
	FInt32Range ZoomRange = FInt32Range(0, 9);
	UPROPERTY(EditAnywhere, Category = "Map Settings")
	float ZoomFactor = 0.8f;

	UPROPERTY(EditAnywhere, Category = "Waypoints Settings")
	float WorldLocationToMapDivider = 22.f;
	UPROPERTY(EditAnywhere, Category = "Waypoints Settings")
	float UpdateWaypointsTime = 1.f;

	// returns a Vector that does not exceed the size of the MapImage
	FVector2D ClampSides(const FGeometry& MyGeometry, FVector2D VectorToClamp);

	UPROPERTY(Transient)
	bool bIsDraggingMap = false;
	UPROPERTY(Transient)
	int32 CurrentZoom = 0;

	void ScaleWaypoints(float ZoomMultiplier);
	void DeleteWaypointsFromMap();
	void UpdateWaypointsInRealTime();
	void UpdateWaypointTransform(TObjectPtr<class UCanvasPanelSlot> WaypointCanvasPanel, const FWaypointOnMap& WaypointOnMap);
	FVector2D TransformWorldLocationToMap(const FVector& VectorToTransform);
	UPROPERTY(Transient)
	TArray<TObjectPtr<UImage>> CurrentWaypointsOnMapImages;
	UPROPERTY(Transient)
	TMap<TObjectPtr<class UCanvasPanelSlot>, FWaypointOnMap> WaypointsToUpdateInRealTime;
	UPROPERTY(Transient)
	FVector2D SavedWaypointRenderScale = FVector2D(1.f);
	UPROPERTY(Transient)
	FTimerHandle UpdateWaypointsHandle = FTimerHandle();

	UPROPERTY(Transient)
	TObjectPtr<class UMapMenuWidget> MapMenuWidget = nullptr;
};
