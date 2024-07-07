// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SortItemsWidget.generated.h"

/**
 * 
 */
class UTextBlock;
class UButton;
class UWrapBox;
UCLASS()
class MEDIEVALDYNASTY_API USortItemsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	FORCEINLINE void SetInventoryMenuWidget(TObjectPtr<class UInventoryMenuWidget> NewInventoryMenuWidget) { InventoryMenuWidget = NewInventoryMenuWidget; }

	void SortItems(const auto& LambdaToSortItems);

	TFunction<bool(const TObjectPtr<UShowItemDataObject>& FirstItem, const TObjectPtr<UShowItemDataObject>& SecondItem)> SavedSortFunction;

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemIconTextBlock = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UWrapBox> ItemNameWrapBox = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemNameTextBlock = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UButton> SortItemNameButton = nullptr;
	UFUNCTION()
	void OnClicked_SortItemNameButton();

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UWrapBox> ItemAmountWrapBox = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemAmountTextBlock = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UButton> SortItemAmountButton = nullptr;
	UFUNCTION()
	void OnClicked_SortItemAmountButton();

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemDurabilityTextBlock = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UWrapBox> ItemWeightWrapBox = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemWeightTextBlock = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UButton> SortItemWeightButton = nullptr;
	UFUNCTION()
	void OnClicked_SortItemWeightButton();

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UWrapBox> ItemPriceWrapBox = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemPriceTextBlock = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UButton> SortItemPriceButton = nullptr;
	UFUNCTION()
	void OnClicked_SortItemPriceButton();

private:

	UPROPERTY(EditDefaultsOnly, Category = "Sorting Items settings")
	FVector2D AscendingSortButtonScale = FVector2D(1.f, 1.f);
	UPROPERTY(EditDefaultsOnly, Category = "Sorting Items settings")
	FVector2D DescendingSortButtonScale = FVector2D(1.f, -1.f);

	UPROPERTY(Transient)
	bool bSortAscendingItemName = true;
	UPROPERTY(Transient)
	bool bSortAscendingItemAmount = true;
	UPROPERTY(Transient)
	bool bSortAscendingItemWeight = true;
	UPROPERTY(Transient)
	bool bSortAscendingItemPrice = true;

	UPROPERTY(Transient)
	TObjectPtr<class UInventoryMenuWidget> InventoryMenuWidget = nullptr;
};
