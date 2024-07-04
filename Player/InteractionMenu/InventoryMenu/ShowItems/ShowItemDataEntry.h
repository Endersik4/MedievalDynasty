// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"

#include "ShowItemDataEntry.generated.h"

class UTextBlock;
UCLASS()
class MEDIEVALDYNASTY_API UShowItemDataEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UButton> SelectItemButton = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UImage> ItemIconImage = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemNameTextBlock = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemAmountTextBlock = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemDurabilityTextBlock = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemWeightTextBlock = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemPriceTextBlock = nullptr;

	UFUNCTION()
	void OnClicked_SelectItemButton();
	UFUNCTION()
	void OnHovered_SelectItemButton();
	UFUNCTION()
	void OnUnhovered_SelectItemButton();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Show Item Data Settings")
	FSlateColor OnHoveredFontColor = FSlateColor();

	void UpdateItemDisplayInformations();

	void ChangeFontColorToAllTextes(const FSlateColor& NewColor);

	UPROPERTY(Transient)
	TObjectPtr<class UShowItemDataObject> ShowItemDataObject = nullptr;

	UPROPERTY(Transient)
	FSlateColor OriginalTextColor = FSlateColor();

};
