// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/StatusAndEquipment/EquipmentOnPlayer/EquipmentOnPlayerEntry.h"
#include "Components/Button.h"

#include "EquipmentOnPlayerEntryObject.h"

void UEquipmentOnPlayerEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	if (!IsValid(ListItemObject))
		return;

	TObjectPtr<UEquipmentOnPlayerEntryObject> EquipmentOnPlayerEntryObject = Cast<UEquipmentOnPlayerEntryObject>(ListItemObject);
	if (!IsValid(EquipmentOnPlayerEntryObject))
		return;

	EquipmentOnPlayerButton->SetStyle(EquipmentOnPlayerEntryObject->EquipmentOnPlayer.EquipmentButtonStyle);
}
