// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/MapMenu/MapMenuWidget.h"

#include "WorldInformationMapWidget.h"
#include "SortWaypoints/SortedMapWaypointsWidget.h"
#include "MapWidget.h"

void UMapMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SortedMapWaypointsWidget->SetMapMenuWidget(this);
	SortedMapWaypointsWidget->FillSortedWaypointsListView();
}
