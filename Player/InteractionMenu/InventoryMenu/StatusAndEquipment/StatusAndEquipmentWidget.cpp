// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu//StatusAndEquipment/StatusAndEquipmentWidget.h"
#include "Components/TileView.h"

#include "Status/PlayerStatusObject.h"
#include "QuickSelect/QuickSelectEntryObject.h"
#include "EquipmentOnPlayer/EquipmentOnPlayerEntryObject.h"
#include "MedievalDynasty/Player/MedievalPlayer.h"

void UStatusAndEquipmentWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Player = Cast<AMedievalPlayer>(GetOwningPlayerPawn());

	FillPlayerStatusTileView();
	FillWeaponShortcutsTileView();
	FillEquipmentTileView();
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

void UStatusAndEquipmentWidget::FillWeaponShortcutsTileView()
{
	for (const FQuickToolSelectEntry& CurrentQuickSelectEntry : QuickSelectEntries)
	{
		TObjectPtr<UQuickSelectEntryObject> QuickSelectEntryObject = NewObject<UQuickSelectEntryObject>();
		if (!IsValid(QuickSelectEntryObject))
			continue;

		QuickSelectEntryObject->QuickSelectEntry = CurrentQuickSelectEntry;
		QuickSelectEntryObject->Player = Player;

		WeaponShortcutsTileView->AddItem(QuickSelectEntryObject);
	}
}

void UStatusAndEquipmentWidget::FillEquipmentTileView()
{
	for (const FEquipmentOnPlayer& CurrentEquipment : AllEquipmentsOnPlayer)
	{
		TObjectPtr<UEquipmentOnPlayerEntryObject> EquipmentOnPlayerObject = NewObject<UEquipmentOnPlayerEntryObject>();
		if (!IsValid(EquipmentOnPlayerObject))
			continue;

		EquipmentOnPlayerObject->EquipmentOnPlayer = CurrentEquipment;
		EquipmentOnPlayerObject->Player = Player;

		EquipmentTileView->AddItem(EquipmentOnPlayerObject);
	}
}
