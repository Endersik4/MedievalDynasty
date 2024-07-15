// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/StatusAndEquipment/EquipmentOnPlayer/EquipmentOnPlayerEntry.h"
#include "Components/Button.h"
#include "Components/Image.h"

#include "EquipmentOnPlayerEntryObject.h"
#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/InventoryMenuWidget.h"
#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/StatusAndEquipment/DragItemWidget.h"

void UEquipmentOnPlayerEntry::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	EquipmentOnPlayerButton->OnHovered.AddDynamic(this, &UEquipmentOnPlayerEntry::OnHovered_EquipmentPlayerButton);

}

void UEquipmentOnPlayerEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	if (!IsValid(ListItemObject))
		return;

	EquipmentOnPlayerEntryObject = Cast<UEquipmentOnPlayerEntryObject>(ListItemObject);
	if (!IsValid(EquipmentOnPlayerEntryObject))
		return;

	EquipmentOnPlayerButton->SetStyle(EquipmentOnPlayerEntryObject->EquipmentOnPlayer.EquipmentButtonStyle);
}

void UEquipmentOnPlayerEntry::OnHovered_EquipmentPlayerButton()
{
	if (!IsValid(EquipmentOnPlayerEntryObject))
		return;

	if (!IsValid(EquipmentOnPlayerEntryObject->InventoryMenuWidget))
		return;

	if (!EquipmentOnPlayerEntryObject->InventoryMenuWidget->GetDraggingItemWidget()->GetIsDraggingItem())
		return;

	const FBaseItemData& DragingItem = EquipmentOnPlayerEntryObject->InventoryMenuWidget->GetDraggingItemWidget()->GetCurrentDragingItem();

	if (DragingItem.EquipmentType != EquipmentOnPlayerEntryObject->EquipmentOnPlayer.CanEquipOnlyEquipmentType)
		return;

	if (!IsValid(DragingItem.ItemIcon))
		return;

	EquipmentIconImage->SetVisibility(ESlateVisibility::HitTestInvisible);
	EquipmentIconImage->SetBrushFromTexture(DragingItem.ItemIcon);
	EquipmentOnPlayerButton->SetStyle(HighlightedOccupiedEquipmentButtonStyle);

	EquipmentOnPlayerEntryObject->bOccupied = true;
}

void UEquipmentOnPlayerEntry::HighlightEquipment(bool bHighlight)
{
	if (!IsValid(EquipmentOnPlayerEntryObject))
		return;

	if (bHighlight)
	{
		if (EquipmentOnPlayerEntryObject->bOccupied)
			EquipmentOnPlayerButton->SetStyle(HighlightedOccupiedEquipmentButtonStyle);
		else
			EquipmentOnPlayerButton->SetStyle(EquipmentOnPlayerEntryObject->EquipmentOnPlayer.HighlightedEquipmentButtonStyle);
	}
	else 
	{
		if (EquipmentOnPlayerEntryObject->bOccupied)
			EquipmentOnPlayerButton->SetStyle(OccupiedEquipmentButtonStyle);
		else 
			EquipmentOnPlayerButton->SetStyle(EquipmentOnPlayerEntryObject->EquipmentOnPlayer.EquipmentButtonStyle);
	}
}
