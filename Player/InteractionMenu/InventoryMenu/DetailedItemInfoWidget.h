// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MedievalDynasty/Player/Inventory/ItemData.h"
#include "DetailedItemInfoWidget.generated.h"

class URichTextBlock;
class UTextBlock;

UCLASS()
class MEDIEVALDYNASTY_API UDetailedItemInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateItemInformation(FBaseItemData* ItemData);

protected:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UImage> BackgroundImage = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UImage> ItemIconImage = nullptr;	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemNameTextBlock = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemDescriptionTextBlock = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<URichTextBlock> ItemInfoDurabilityRichTextBlock = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UImage> ItemDurabilityIconImage = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<URichTextBlock> ItemInfoWeightRichTextBlock = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<URichTextBlock> ItemInfoPriceRichTextBlock = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<URichTextBlock> ItemInfoStorageRichTextBlock = nullptr;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Detatiled Item Info Settings")
	TObjectPtr<UTexture2D> DurabilityType_Uses_Texture = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Detatiled Item Info Settings")
	TObjectPtr<UTexture2D> DurabilityType_DestroyOverTime_Texture = nullptr;
};
