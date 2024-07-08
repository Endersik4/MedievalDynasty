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

public:
	void DeselectShowItemEntry();

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
	void OnPressed_SelectItemButton();
	UFUNCTION()
	void OnReleased_SelectItemButton();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Show Item Data Settings")
	FSlateColor OnHoveredFontColor = FSlateColor();
	UPROPERTY(EditDefaultsOnly, Category = "Show Item Data Settings")
	FButtonStyle ItemSelectedButtonStyle = FButtonStyle();

	void UpdateItemDisplayInformations();

	void ChangeFontColorToAllTextes(const FSlateColor& NewColor);

	UPROPERTY(Transient)
	TObjectPtr<class UShowItemDataObject> ShowItemDataObject = nullptr;

	UPROPERTY(Transient)
	FSlateColor OriginalTextColor = FSlateColor();
	UPROPERTY(Transient)
	FButtonStyle OriginalSelectItemButtonStyle = FButtonStyle();
};
