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
	TObjectPtr<URichTextBlock> ItemInformationRichTextBlock = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemDescriptionTextBlock = nullptr;


};
