// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MedievalDynasty/Player/Inventory/ItemData.h"
#include "InventoryMenuWidget.generated.h"

USTRUCT(BlueprintType)
struct FCategoryInventory
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere)
	bool bDivideItemsUsingCategory = false;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bDivideItemsUsingCategory"))
	TEnumAsByte<EItemType> CategoryType = EIT_Miscellaneous;
	UPROPERTY(EditAnywhere)
	FButtonStyle SelectCategoryButtonStyle = FButtonStyle();
	UPROPERTY(EditAnywhere)
	FButtonStyle CategorySelectedButtonStyle = FButtonStyle();
	UPROPERTY(EditAnywhere)
	FText CategoryDisplayText = FText();

	FCategoryInventory()
	{
		bDivideItemsUsingCategory = false;
		CategoryType = EIT_Miscellaneous;
		SelectCategoryButtonStyle = FButtonStyle();
		CategoryDisplayText = FText();
	}

	FCategoryInventory(bool _bDivideItemsUsingCategory, EItemType _CategoryType)
	{
		bDivideItemsUsingCategory = _bDivideItemsUsingCategory;
		CategoryType = _CategoryType;
	}
};

class UTextBlock;
class URichTextBlock;
class UImage;
UCLASS()
class MEDIEVALDYNASTY_API UInventoryMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateInventory(bool bDivideWithCategory = false, EItemType CategoryTypeToDivide = EIT_Miscellaneous);
	void UpdateCategoryDisplayText(const FText& NewCategoryDisplayText);
	void UpdateCategory(TObjectPtr<class USelectCategoryInventoryEntry> NewCurrentSelectedCategoryEntry);

	void SetSelectedShowItemDataEntry(TObjectPtr<class UShowItemDataEntry> NewSelectedShowItemDataEntry);

	UFUNCTION()
	void OnClicked_ShowItemDataEntry(class UShowItemDataObject* Item);

	FORCEINLINE TObjectPtr<class UListView> GetCategoryInventoryListView() const {return CategoryInventoryListView;}

	FORCEINLINE void SetPlayerInventoryComponent(TObjectPtr<class UInventoryComponent> NewInventoryComponent) { PlayerInventoryComponent = NewInventoryComponent; }

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UImage> BackgroundImage = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UTileView> SelectCategoryInventoryTileView = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UListView> CategoryInventoryListView = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> NoItemsDisplayTextBlock = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> MoneyDisplayTextBlock = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> WeightDisplayTextBlock = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UHorizontalBox> CategoryNameHorizontalBox = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> CategoryDisplayName = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UImage> LeftCategoryDecorationImage = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UImage> RightCategoryDecorationImage = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<URichTextBlock> WeightInformationRichTextBlock = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<URichTextBlock> MoneyInformationRichTextBlock = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UDetailedItemInfoWidget> DetailedItemInfoWidget = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class USortItemsWidget> SortItemsWidget = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UStatusAndEquipmentWidget> StatusAndEquipmentWidget = nullptr;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Inventory Settings")
	TEnumAsByte<EItemType> InitiallCategoryType = EIT_None;
	UPROPERTY(EditDefaultsOnly, Category = "Inventory Settings")
	TArray<FCategoryInventory> AllCategoryToDivideItems = {FCategoryInventory()};
	UPROPERTY(EditDefaultsOnly, Category = "Inventory Settings")
	FSlateColor WeightColorWhenExceeded = FSlateColor(FColor::Red);

	void FillSelectCategoryInventoryTileView();

	void UpdatePlayerStatus();
	void UpdateWeight(TObjectPtr<class UPlayerStatusComponent> PlayerStatusComponent);
	UPROPERTY(Transient)
	FSlateColor OriginalWeightColor = FSlateColor();

	UPROPERTY(Transient)
	bool bFirstTimeSort = true;
	// when inventory is spawned then sort items by name
	void SortItemsByNameDescending();
	
	UPROPERTY(Transient)
	TObjectPtr<class UShowItemDataEntry> SelectedShowItemDataEntry = nullptr;
	UPROPERTY(Transient)
	TObjectPtr<class USelectCategoryInventoryEntry> CurrentSelectedCategoryEntry = nullptr;
	UPROPERTY(Transient)
	TObjectPtr<class UInventoryComponent> PlayerInventoryComponent = nullptr;
	UPROPERTY(Transient)
	TObjectPtr<class AMedievalPlayer> Player = nullptr;
};


