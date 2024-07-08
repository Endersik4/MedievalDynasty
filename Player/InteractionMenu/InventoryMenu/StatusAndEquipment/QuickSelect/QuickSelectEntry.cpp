// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/StatusAndEquipment/QuickSelect/QuickSelectEntry.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"

#include "QuickSelectEntryObject.h"
#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/InventoryMenuWidget.h"
#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/StatusAndEquipment/DragItemWidget.h"

void UQuickSelectEntry::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	QuickSelectButton->OnPressed.AddDynamic(this, &UQuickSelectEntry::OnPressed_QuickSelectButton);
	QuickSelectButton->OnReleased.AddDynamic(this, &UQuickSelectEntry::OnReleased_QuickSelectButton);

	QuickSelectButton->OnHovered.AddDynamic(this, &UQuickSelectEntry::OnHovered_QuickSelectButton);
	QuickSelectButton->OnUnhovered.AddDynamic(this, &UQuickSelectEntry::OnUnhovered_QuickSelectButton);
}

void UQuickSelectEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	if (!IsValid(ListItemObject))
		return;

	QuickSelectEntryObject = Cast<UQuickSelectEntryObject>(ListItemObject);
	if (!IsValid(QuickSelectEntryObject))
		return;

	QuickSelectNumberText->SetText(FText::AsNumber(QuickSelectEntryObject->QuickSelectEntry.QuickAttackNum));
}

void UQuickSelectEntry::OnPressed_QuickSelectButton()
{
	if (!IsValid(QuickSelectEntryObject))
		return;
	if (!IsValid(QuickSelectEntryObject->InventoryMenuWidget))
		return;

	if (!QuickSelectEntryObject->bQuickSelectOccupied)
		return;

	TObjectPtr<UDragItemWidget> DraggingItemWidget = QuickSelectEntryObject->InventoryMenuWidget->GetDraggingItemWidget();
	if (!IsValid(DraggingItemWidget))
		return;

	DraggingItemWidget->ItemFoundNewSlotFunc = [this]() {this->ItemFoundNewSlot(); };
	DraggingItemWidget->StartDraggingItem(QuickSelectEntryObject->ItemInQuickSelect, 
		GetTickSpaceGeometry().LocalToAbsolute(QuickSelectButton->GetRenderTransform().Translation));
}

void UQuickSelectEntry::OnReleased_QuickSelectButton()
{
	if (!IsValid(QuickSelectEntryObject))
		return;

	if (!QuickSelectEntryObject->bQuickSelectOccupied)
		return;

	QuickSelectEntryObject->InventoryMenuWidget->GetDraggingItemWidget()->StopDraggingItem();
}

void UQuickSelectEntry::OnHovered_QuickSelectButton()
{
	if (!IsValid(QuickSelectEntryObject))
		return;

	if (!IsValid(QuickSelectEntryObject->InventoryMenuWidget))
		return;

	TObjectPtr<UDragItemWidget> DraggingItemWidget = QuickSelectEntryObject->InventoryMenuWidget->GetDraggingItemWidget();
	if (!IsValid(DraggingItemWidget))
		return;

	if (!DraggingItemWidget->GetIsDraggingItem())
		return;
	
	QuickSelectEntryObject->ItemInQuickSelect = DraggingItemWidget->GetCurrentDragingItem();
	if (CanEquipOnlyItemType != QuickSelectEntryObject->ItemInQuickSelect.ItemType || QuickSelectEntryObject->ItemInQuickSelect.EquipmentType != EET_None)
		return;

	QuickSelectEntryObject->bQuickSelectOccupied = true;
	if (DraggingItemWidget->ItemFoundNewSlotFunc)
		DraggingItemWidget->ItemFoundNewSlotFunc();

	if (IsValid(QuickSelectEntryObject->ItemInQuickSelect.ItemIcon))
	{
		ToolIconImage->SetVisibility(ESlateVisibility::HitTestInvisible);
		ToolIconImage->SetBrushFromTexture(QuickSelectEntryObject->ItemInQuickSelect.ItemIcon);
	}
}

void UQuickSelectEntry::OnUnhovered_QuickSelectButton()
{
	;
}

void UQuickSelectEntry::ItemFoundNewSlot()
{
	QuickSelectEntryObject->bQuickSelectOccupied = false;
	ToolIconImage->SetVisibility(ESlateVisibility::Hidden);

}
