// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WaypointData.generated.h"

USTRUCT(BlueprintType)
struct FWaypoint
{
	GENERATED_USTRUCT_BODY();

private:
	UPROPERTY(EditAnywhere)
	FName WaypointOnMapRowName = FName();

public:
	// if WaypointWorldLocation == 0 then use World Location from Data Table
	UPROPERTY(EditAnywhere)
	FVector WaypointWorldLocation = FVector();
	// If true then update waypoint location on map in Timer
	UPROPERTY(EditAnywhere)
	bool bTrackLocation = false;
	// If true then update waypoint rotation on map in Timer
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bTrackLocation", EditConditionHides))
	bool bTrackRotation = false;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bTrackLocation", EditConditionHides))
	bool bCustomTransformFunction = false;
	// If ActorToTrack is Invalid with bTrackLocation == true then ActorToTrack is the owner
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bTrackLocation && !bCustomTransformFunction", EditConditionHides))
	TObjectPtr<AActor> ActorToTrack = nullptr;

	FWaypoint()
	{
		WaypointOnMapRowName = FName();
		bCustomTransformFunction = false;
		bTrackLocation = false;
		bTrackRotation = false;
		ActorToTrack = nullptr;
	}

	FWaypoint(FName _WaypointOnMapRowName, bool _bCustomTransformFunction, bool _bTrackLocation, bool _bTrackRotation, TObjectPtr<AActor> _ActorToTrack)
	{
		WaypointOnMapRowName = _WaypointOnMapRowName;
		bCustomTransformFunction = _bCustomTransformFunction;
		bTrackLocation = _bTrackLocation;
		bTrackRotation = _bTrackRotation;
		ActorToTrack = _ActorToTrack;
	}
};

UENUM(BlueprintType)
enum EWaypointSortCategory
{
	EWSC_Main UMETA(DisplayName = "Main"),
	EWSC_People UMETA(DisplayName = "People"),
	EWSC_Tasks UMETA(DisplayName = "Tasks"),
	EWSC_AllBuidings UMETA(DisplayName = "AllBuidings"),
	EWSC_Houses UMETA(DisplayName = "Houses"),
	EWSC_Maining UMETA(DisplayName = "Maining"),
	EWSC_Hunting UMETA(DisplayName = "Hunting"),
	EWSC_Farming UMETA(DisplayName = "Farming"),
};

USTRUCT(BlueprintType)
struct FWaypointOnMap : public FTableRowBase, public FWaypoint
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere)
	FText WaypointDisplayName = FText();
	UPROPERTY(EditAnywhere)
	TObjectPtr<UTexture2D> WaypointIcon = nullptr;
	UPROPERTY(EditAnywhere)
	FVector2D InitialWaypointIconSize = FVector2D();
	// When true, Waypoint will not be displayed in the category list.
	UPROPERTY(EditAnywhere)
	bool bIgnoreCategory = false;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "!bIgnoreCategory"))
	TArray<TEnumAsByte<EWaypointSortCategory>> CategoriesForWaypoint;

	FWaypointOnMap()
	{
		WaypointDisplayName = FText();
		WaypointIcon = nullptr;
		InitialWaypointIconSize = FVector2D();
		bTrackLocation = false;
		ActorToTrack = nullptr;
	}
};

USTRUCT(BlueprintType)
struct FWaypointSort
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EWaypointSortCategory> WaypointCategoryType = EWSC_Main;
	UPROPERTY(EditAnywhere)
	FText WaypointSortDisplayName = FText();

	TArray<FWaypointOnMap> AllSortedWaypoints;
};

UCLASS()
class MEDIEVALDYNASTY_API UWaypointData : public UObject
{
	GENERATED_BODY()
	
};
