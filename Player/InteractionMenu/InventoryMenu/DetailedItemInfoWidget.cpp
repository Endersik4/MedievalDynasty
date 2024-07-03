// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/DetailedItemInfoWidget.h"
#include "Components/RichTextBlock.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UDetailedItemInfoWidget::UpdateItemInformation(FBaseItemData* ItemData)
{
	if (!ItemData)
		return;

	ItemIconImage->SetBrushFromTexture(ItemData->ItemIcon, true);
	ItemNameTextBlock->SetText(ItemData->ItemDisplayText);
	ItemDescriptionTextBlock->SetText(ItemData->ItemDisplayDescription);

	FString ItemInformations = FString::SanitizeFloat(ItemData->ItemDurability) + FString::SanitizeFloat(ItemData->ItemWeight) 
		+ FString::SanitizeFloat(ItemData->ItemPrice) + ItemData->ItemStorageName.ToString();
	ItemInformationRichTextBlock->SetText(FText::FromString(ItemInformations));
}
