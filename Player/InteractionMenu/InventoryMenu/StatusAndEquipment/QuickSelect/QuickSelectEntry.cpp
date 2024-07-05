// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/StatusAndEquipment/QuickSelect/QuickSelectEntry.h"
#include "Components/TextBlock.h"

#include "QuickSelectEntryObject.h"

void UQuickSelectEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	if (!IsValid(ListItemObject))
		return;

	TObjectPtr<UQuickSelectEntryObject> QuickSelectEntryObject = Cast<UQuickSelectEntryObject>(ListItemObject);
	if (!IsValid(QuickSelectEntryObject))
		return;

	QuickSelectNumberText->SetText(FText::AsNumber(QuickSelectEntryObject->QuickSelectEntry.QuickAttackNum));
}
