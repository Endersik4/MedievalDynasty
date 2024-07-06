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

	FString ItemInformations = FString::SanitizeFloat(ItemData->ItemDurability, 0);
	if (ItemData->DurabilityType == EDT_DestroyOverTime)
	{
		ItemInformations += "%";
		ItemDurabilityIconImage->SetBrushFromTexture(DurabilityType_DestroyOverTime_Texture, true);
	}
	else if (ItemData->DurabilityType == EDT_Uses)
	{
		ItemInformations += " / " + FString::SanitizeFloat(ItemData->ItemInitallDurability, 0);
		ItemDurabilityIconImage->SetBrushFromTexture(DurabilityType_Uses_Texture, true);
	}
	ItemInfoDurabilityRichTextBlock->SetText(FText::FromString(ItemInformations));

	ItemInformations = FString::SanitizeFloat(ItemData->ItemWeight, 0) + " kg";
	ItemInfoWeightRichTextBlock->SetText(FText::FromString(ItemInformations));

	ItemInformations = FString::SanitizeFloat(ItemData->ItemPrice, 0);
	ItemInfoPriceRichTextBlock->SetText(FText::FromString(ItemInformations));

	ItemInfoStorageRichTextBlock->SetText(ItemData->ItemStorageName);
}
