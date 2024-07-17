// Copyright Adam Bartela. All Rights Reserved


#include "SortWaypointEntryWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "SortWaypointEntryObject.h"

void USortWaypointEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	if (!IsValid(ListItemObject))
		return;

	TObjectPtr<USortWaypointEntryObject> SortWaypointEntryObject = Cast<USortWaypointEntryObject>(ListItemObject);
	if (!IsValid(SortWaypointEntryObject))
		return;


	if (SortWaypointEntryObject->WaypointIcon)
		WaypointIconImage->SetBrushFromTexture(SortWaypointEntryObject->WaypointIcon);

	WaypointDisplayText->SetText(SortWaypointEntryObject->WaypointDisplayText);
}
