// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WaypointData.h"
#include "MapMenuWidget.generated.h"

class UTextBlock;
class UWrapBox;
class UImage;
UCLASS()
class MEDIEVALDYNASTY_API UMapMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetCurrentWaypointsOnMapIndex(int32 NewCurrentWaypointsOnMapIndex) { CurrentWaypointsOnMapIndex = NewCurrentWaypointsOnMapIndex; }

	FORCEINLINE int32 GetCurrentWaypointsOnMapIndex() const {return CurrentWaypointsOnMapIndex;}
	FORCEINLINE const TArray<FWaypointSort>& GetSortedWaypointsToCategory() const {return SortedWaypointsToCategory;}

	void UpdateWaypoints();

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UWorldInformationMapWidget> WorldInformationWidget = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class USortedMapWaypointsWidget> SortedMapWaypointsWidget = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UMapWidget> MapWidget = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UImage> BackgroundImageForMap = nullptr;


private:
	UPROPERTY(EditAnywhere, Category = "Waypoints settings")
	TArray<FWaypointSort> SortedWaypointsToCategory;

	UPROPERTY(Transient)
	int32 CurrentWaypointsOnMapIndex = 0;
};
