// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/MapMenu/MapMenuWidget.h"

#include "WorldInformationMapWidget.h"
#include "SortWaypoints/SortedMapWaypointsWidget.h"
#include "MapWidget.h"
#include "MedievalDynasty/Player/MedievalPlayer.h"

void UMapMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	MapWidget->SetMapMenuWidget(this);
	SortedMapWaypointsWidget->SetMapMenuWidget(this);
	SortedMapWaypointsWidget->FillSortedWaypointsListView();
}

void UMapMenuWidget::UpdateWaypoints()
{
	TObjectPtr<AMedievalPlayer> Player = Cast<AMedievalPlayer>(GetOwningPlayerPawn());
	if (!IsValid(Player))
		return;

	TObjectPtr<UDataTable> WaypointsDataTable = Player->GetWaypointsDataTable();
	if (!IsValid(WaypointsDataTable))
		return;

	SortedWaypointsToCategory[CurrentWaypointsOnMapIndex].AllSortedWaypoints.Empty();

	for (const FWaypoint& CurrentWaypoint : Player->GetAllWaypoints())
	{
		FWaypointOnMap* WaypointOnMap = WaypointsDataTable->FindRow<FWaypointOnMap>(CurrentWaypoint.WaypointOnMapRowName, "");
		if (!WaypointOnMap)
			continue;

		FWaypointOnMap TempWaypoint = *WaypointOnMap;
		TempWaypoint = CurrentWaypoint;

		if (!WaypointOnMap->bIgnoreCategory && !WaypointOnMap->bVisibiltyNotAffectedByCategory)
		{
			const int32 FoundWaypointIndexInCategory = WaypointOnMap->CategoriesForWaypoint.Find(SortedWaypointsToCategory[CurrentWaypointsOnMapIndex].WaypointCategoryType);
			if (FoundWaypointIndexInCategory == INDEX_NONE)
				continue;
		}

		if (SortedWaypointsToCategory[CurrentWaypointsOnMapIndex].AllSortedWaypoints.FindByKey(TempWaypoint))
		{
			TempWaypoint.bIgnoreCategory = true;
		}
		
		SortedWaypointsToCategory[CurrentWaypointsOnMapIndex].AllSortedWaypoints.Add(TempWaypoint);
	}

	MapWidget->UpdateWaypointsOnMap();
}
