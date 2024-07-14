// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "MapMenuWidget.generated.h"

USTRUCT(BlueprintType)
struct FWaypointOnMap
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere)
	FString WaypointName = FString();
	UPROPERTY(EditAnywhere)
	FVector WaypointWorldLocation = FVector();
	UPROPERTY(EditAnywhere)
	FText WaypointDisplayName = FText();
	UPROPERTY(EditAnywhere)
	TObjectPtr<UTexture2D> WaypointIcon = nullptr;
};

USTRUCT(BlueprintType)
struct FWaypointSort
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere)
	FText WaypointSortDisplayName = FText();
	UPROPERTY(EditAnywhere)
	TArray<FWaypointOnMap> Waypoints;
};

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
	FORCEINLINE const TArray<FWaypointSort>& GetAllWaypointsOnMap() const {return AllWaypointsOnMap;}

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
	TArray<FWaypointSort> AllWaypointsOnMap;

	UPROPERTY(Transient)
	int32 CurrentWaypointsOnMapIndex = 0;
};
