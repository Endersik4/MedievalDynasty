// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/ShowItems/ShowItemDataEntry.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"

#include "ShowItemDataObject.h"
#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/InventoryMenuWidget.h"
#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/StatusAndEquipment/DragItemWidget.h"

void UShowItemDataEntry::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SelectItemButton->OnPressed.AddDynamic(this, &UShowItemDataEntry::OnPressed_SelectItemButton);
	SelectItemButton->OnReleased.AddDynamic(this, &UShowItemDataEntry::OnReleased_SelectItemButton);

	OriginalTextColor = ItemAmountTextBlock->GetColorAndOpacity();
	OriginalSelectItemButtonStyle = SelectItemButton->GetStyle();
}

void UShowItemDataEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	if (!IsValid(ListItemObject))
		return;
	
	ShowItemDataObject = Cast<UShowItemDataObject>(ListItemObject);
	if (!IsValid(ShowItemDataObject))
		return;

	if (ShowItemDataObject->bInitallySelectedItem)
	{
		OnPressed_SelectItemButton();
		OnReleased_SelectItemButton();
		ShowItemDataObject->bInitallySelectedItem = false;
	}

	UpdateItemDisplayInformations();

}

void UShowItemDataEntry::UpdateItemDisplayInformations()
{
	if (!IsValid(ShowItemDataObject))
		return;

	if (IsValid(ShowItemDataObject->ItemData.ItemIcon))
		ItemIconImage->SetBrushFromTexture(ShowItemDataObject->ItemData.ItemIcon);
	
	ItemNameTextBlock->SetText(ShowItemDataObject->ItemData.ItemDisplayText);
	ItemAmountTextBlock->SetText(FText::AsNumber(ShowItemDataObject->ItemAmount));

	const FString ItemDurability = FString::FromInt(FMath::FloorToInt32(ShowItemDataObject->ItemData.ItemDurability)) + "%";
	ItemDurabilityTextBlock->SetText(FText::FromString(ItemDurability));

	ItemWeightTextBlock->SetText(FText::AsNumber(ShowItemDataObject->ItemData.ItemWeight * ShowItemDataObject->ItemAmount));

	ItemPriceTextBlock->SetText(FText::AsNumber(ShowItemDataObject->ItemData.ItemPrice));

}

void UShowItemDataEntry::OnPressed_SelectItemButton()
{
	if (!IsValid(ShowItemDataObject))
		return;

	if (!IsValid(ShowItemDataObject->InventoryMenuWidget))
		return;

	if (!ShowItemDataObject->bItemSelected)
	{
		ShowItemDataObject->InventoryMenuWidget->OnClicked_ShowItemDataEntry(ShowItemDataObject);
		ShowItemDataObject->InventoryMenuWidget->SetSelectedShowItemDataEntry(this);
		ChangeFontColorToAllTextes(OnHoveredFontColor);
		SelectItemButton->SetStyle(ItemSelectedButtonStyle);

		if (ShowItemDataObject->ItemData.EquipmentType != EET_None)
		{
			ShowItemDataObject->InventoryMenuWidget->HighlightEquipmentOnPlayer(true, ShowItemDataObject->ItemData);
		}

		ShowItemDataObject->bItemSelected = true;
	}
	
	TObjectPtr<class UCanvasPanelSlot> SelectItemButtonCanvasSlot = Cast<UCanvasPanelSlot>(ItemIconImage->Slot);
	if (!IsValid(SelectItemButtonCanvasSlot))
		return;
	
	ShowItemDataObject->InventoryMenuWidget->GetDraggingItemWidget()->StartDraggingItem(ShowItemDataObject->ItemData, GetTickSpaceGeometry().LocalToAbsolute(SelectItemButtonCanvasSlot->GetPosition()));
}

void UShowItemDataEntry::OnReleased_SelectItemButton()
{
	ShowItemDataObject->InventoryMenuWidget->GetDraggingItemWidget()->StopDraggingItem();
}

void UShowItemDataEntry::DeselectShowItemEntry()
{
	ChangeFontColorToAllTextes(OriginalTextColor);
	SelectItemButton->SetStyle(OriginalSelectItemButtonStyle);
	ShowItemDataObject->bItemSelected = false;

	if (!IsValid(ShowItemDataObject))
		return;

	if (ShowItemDataObject->ItemData.EquipmentType != EET_None)
	{
		ShowItemDataObject->InventoryMenuWidget->HighlightEquipmentOnPlayer(false, ShowItemDataObject->ItemData);
	}
}

void UShowItemDataEntry::ChangeFontColorToAllTextes(const FSlateColor& NewColor)
{
	ItemNameTextBlock->SetColorAndOpacity(NewColor);
	ItemAmountTextBlock->SetColorAndOpacity(NewColor);
	ItemDurabilityTextBlock->SetColorAndOpacity(NewColor);
	ItemWeightTextBlock->SetColorAndOpacity(NewColor);
	ItemPriceTextBlock->SetColorAndOpacity(NewColor);
}

