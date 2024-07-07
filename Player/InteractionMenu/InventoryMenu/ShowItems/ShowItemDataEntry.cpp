// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/ShowItems/ShowItemDataEntry.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "ShowItemDataObject.h"
#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/InventoryMenuWidget.h"

void UShowItemDataEntry::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SelectItemButton->OnClicked.AddDynamic(this, &UShowItemDataEntry::OnClicked_SelectItemButton);
	SelectItemButton->OnHovered.AddDynamic(this, &UShowItemDataEntry::OnHovered_SelectItemButton);
	SelectItemButton->OnUnhovered.AddDynamic(this, &UShowItemDataEntry::OnUnhovered_SelectItemButton);

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
		OnClicked_SelectItemButton();
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

void UShowItemDataEntry::OnClicked_SelectItemButton()
{
	if (!IsValid(ShowItemDataObject))
		return;

	if (!IsValid(ShowItemDataObject->InventoryMenuWidget))
		return;

	ShowItemDataObject->InventoryMenuWidget->OnClicked_ShowItemDataEntry(ShowItemDataObject);
	ShowItemDataObject->InventoryMenuWidget->SetSelectedShowItemDataEntry(this);
	ChangeFontColorToAllTextes(OnHoveredFontColor);
	SelectItemButton->SetStyle(ItemSelectedButtonStyle);
}

void UShowItemDataEntry::OnHovered_SelectItemButton()
{
	;
}

void UShowItemDataEntry::OnUnhovered_SelectItemButton()
{
	;
}

void UShowItemDataEntry::DeselectShowItemEntry()
{
	ChangeFontColorToAllTextes(OriginalTextColor);
	SelectItemButton->SetStyle(OriginalSelectItemButtonStyle);
}

void UShowItemDataEntry::ChangeFontColorToAllTextes(const FSlateColor& NewColor)
{
	ItemNameTextBlock->SetColorAndOpacity(NewColor);
	ItemAmountTextBlock->SetColorAndOpacity(NewColor);
	ItemDurabilityTextBlock->SetColorAndOpacity(NewColor);
	ItemWeightTextBlock->SetColorAndOpacity(NewColor);
	ItemPriceTextBlock->SetColorAndOpacity(NewColor);
}
