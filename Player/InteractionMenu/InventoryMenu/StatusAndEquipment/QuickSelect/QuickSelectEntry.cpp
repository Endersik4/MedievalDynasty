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

void UQuickSelectEntry::OnHovered_QuickSelectButton()
{
	if (!IsValid(QuickSelectEntryObject))
		return;

	if (!IsValid(QuickSelectEntryObject->InventoryMenuWidget))
		return;

	if (!QuickSelectEntryObject->InventoryMenuWidget->GetDraggingItemWidget()->GetIsDraggingItem())
		return;

	const FBaseItemData& DragingItem = QuickSelectEntryObject->InventoryMenuWidget->GetDraggingItemWidget()->GetCurrentDragingItem();
	if (CanEquipOnlyItemType != DragingItem.ItemType || DragingItem.EquipmentType != EET_None)
		return;

	if (IsValid(DragingItem.ItemIcon))
	{
		ToolIconImage->SetVisibility(ESlateVisibility::HitTestInvisible);
		ToolIconImage->SetBrushFromTexture(DragingItem.ItemIcon);
	}
}

void UQuickSelectEntry::OnUnhovered_QuickSelectButton()
{
	;
}
