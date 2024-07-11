// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/MapMenu/SortedMapWaypointsWidget.h"
#include "Components/ListView.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "MapMenuWidget.h"
#include "SortWaypointEntryObject.h"

void USortedMapWaypointsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	LeftChoice_SortButton->OnPressed.AddDynamic(this, &USortedMapWaypointsWidget::OnPressed_LeftChoice_SortButton);
	RightChoice_SortButton->OnPressed.AddDynamic(this, &USortedMapWaypointsWidget::OnPressed_RightChoice_SortButton);
}

void USortedMapWaypointsWidget::OnPressed_LeftChoice_SortButton()
{
	if (!IsValid(MapMenuWidget))
		return;

	const int32 CurrentWaypointsOnMapIndex = MapMenuWidget->GetCurrentWaypointsOnMapIndex();

	if (CurrentWaypointsOnMapIndex - 1 < 0)
	{
		MapMenuWidget->SetCurrentWaypointsOnMapIndex(MapMenuWidget->GetAllWaypointsOnMap().Num() - 1);
	}
	else 
	{
		MapMenuWidget->SetCurrentWaypointsOnMapIndex(CurrentWaypointsOnMapIndex - 1);
	}

	FillSortedWaypointsListView();
}

void USortedMapWaypointsWidget::OnPressed_RightChoice_SortButton()
{
	if (!IsValid(MapMenuWidget))
		return;

	const int32 CurrentWaypointsOnMapIndex = MapMenuWidget->GetCurrentWaypointsOnMapIndex();

	if (CurrentWaypointsOnMapIndex + 1 >= MapMenuWidget->GetAllWaypointsOnMap().Num())
	{
		MapMenuWidget->SetCurrentWaypointsOnMapIndex(0);
	}
	else 
	{
		MapMenuWidget->SetCurrentWaypointsOnMapIndex(CurrentWaypointsOnMapIndex + 1);
	}

	FillSortedWaypointsListView();
}

void USortedMapWaypointsWidget::FillSortedWaypointsListView()
{
	if (!IsValid(MapMenuWidget))
		return;

	SortedWaypointsListView->ClearListItems();

	const TArray<FWaypointSort> AllWaypoints = MapMenuWidget->GetAllWaypointsOnMap();
	const int32& CurrentWaypointsOnMapIndex = MapMenuWidget->GetCurrentWaypointsOnMapIndex();

	if (CurrentWaypointsOnMapIndex >= AllWaypoints.Num() || CurrentWaypointsOnMapIndex < 0)
		return;

	SortDisplayNameTextBlock->SetText(AllWaypoints[CurrentWaypointsOnMapIndex].WaypointSortDisplayName);

	for (const FWaypointOnMap& CurrentWaypoint : AllWaypoints[CurrentWaypointsOnMapIndex].Waypoints)
	{
		TObjectPtr<USortWaypointEntryObject> SortWaypointEntryObject = NewObject<USortWaypointEntryObject>();
		if (!IsValid(SortWaypointEntryObject))
			return;

		SortWaypointEntryObject->WaypointOnMap = CurrentWaypoint;

		SortedWaypointsListView->AddItem(SortWaypointEntryObject);
	}
}