// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/ShowItems/ShowItemDataEntry.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "ShowItemDataObject.h"

void UShowItemDataEntry::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void UShowItemDataEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{

	if (!IsValid(ListItemObject))
		return;
	
	ShowItemDataObject = Cast<UShowItemDataObject>(ListItemObject);
	if (!IsValid(ShowItemDataObject))
		return;

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
