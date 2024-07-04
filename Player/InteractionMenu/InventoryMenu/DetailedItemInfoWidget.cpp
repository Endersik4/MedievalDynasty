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

	FString ItemInformations = FString::SanitizeFloat(ItemData->ItemDurability, 0) + "%";
	ItemInfoDurabilityRichTextBlock->SetText(FText::FromString(ItemInformations));

	ItemInformations = FString::SanitizeFloat(ItemData->ItemWeight, 0) + " kg";
	ItemInfoWeightRichTextBlock->SetText(FText::FromString(ItemInformations));

	ItemInformations = FString::SanitizeFloat(ItemData->ItemPrice, 0);
	ItemInfoPriceRichTextBlock->SetText(FText::FromString(ItemInformations));

	ItemInfoStorageRichTextBlock->SetText(ItemData->ItemStorageName);
}
