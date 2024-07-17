// Copyright Adam Bartela. All Rights Reserved


#include "SortedMapWaypointsWidget.h"
#include "Components/ListView.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "MedievalDynasty/Player/InteractionMenu/MapMenu/MapMenuWidget.h"
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
		MapMenuWidget->SetCurrentWaypointsOnMapIndex(MapMenuWidget->GetSortedWaypointsToCategory().Num() - 1);
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

	if (CurrentWaypointsOnMapIndex + 1 >= MapMenuWidget->GetSortedWaypointsToCategory().Num())
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

	MapMenuWidget->UpdateWaypoints();

	const TArray<FWaypointSort> SortedWaypointsToCategory = MapMenuWidget->GetSortedWaypointsToCategory();
	const int32& CurrentWaypointsOnMapIndex = MapMenuWidget->GetCurrentWaypointsOnMapIndex();

	if (CurrentWaypointsOnMapIndex >= SortedWaypointsToCategory.Num() || CurrentWaypointsOnMapIndex < 0)
		return;

	SortDisplayNameTextBlock->SetText(SortedWaypointsToCategory[CurrentWaypointsOnMapIndex].WaypointSortDisplayName);

	for (const FWaypointOnMap& CurrentWaypoint : SortedWaypointsToCategory[CurrentWaypointsOnMapIndex].AllSortedWaypoints)
	{
		if (CurrentWaypoint.bIgnoreCategory)
			continue;

		TObjectPtr<USortWaypointEntryObject> SortWaypointEntryObject = NewObject<USortWaypointEntryObject>();
		if (!IsValid(SortWaypointEntryObject))
			return;

		SortWaypointEntryObject->WaypointDisplayText = CurrentWaypoint.WaypointDisplayName;
		SortWaypointEntryObject->WaypointIcon = CurrentWaypoint.WaypointIcon;

		SortedWaypointsListView->AddItem(SortWaypointEntryObject);
	}
}