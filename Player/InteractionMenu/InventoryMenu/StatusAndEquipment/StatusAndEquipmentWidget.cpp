// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu//StatusAndEquipment/StatusAndEquipmentWidget.h"
#include "Components/TileView.h"

#include "Status/PlayerStatusObject.h"
#include "MedievalDynasty/Player/MedievalPlayer.h"

void UStatusAndEquipmentWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Player = Cast<AMedievalPlayer>(GetOwningPlayerPawn());

	FillPlayerStatusTileView();
}

void UStatusAndEquipmentWidget::FillPlayerStatusTileView()
{
	for (const FStatusEntry& CurrentStatusEntry : StatusEntries)
	{
		TObjectPtr<UPlayerStatusObject> PlayerStatusObject = NewObject<UPlayerStatusObject>();
		if (!IsValid(PlayerStatusObject))
			continue;

		PlayerStatusObject->StatusEntry = CurrentStatusEntry;
		PlayerStatusObject->Player = Player;

		PlayerStatusTileView->AddItem(PlayerStatusObject);
	}
}
