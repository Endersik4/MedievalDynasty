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

	FCategoryInventory()
	{
		bDivideItemsUsingCategory = false;
		CategoryType = EIT_Miscellaneous;
	}

	FCategoryInventory(bool _bDivideItemsUsingCategory, EItemType _CategoryType)
	{
		bDivideItemsUsingCategory = _bDivideItemsUsingCategory;
		CategoryType = _CategoryType;
	}
};

class UTextBlock;
class URichTextBlock;
UCLASS()
class MEDIEVALDYNASTY_API UInventoryMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateInventory(bool bDivideWithCategory = false, EItemType CategoryTypeToDivide = EIT_Miscellaneous);

	FORCEINLINE void SetPlayerInventoryComponent(TObjectPtr<class UInventoryComponent> NewInventoryComponent) { PlayerInventoryComponent = NewInventoryComponent; }

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UImage> BackgroundImage = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UTileView> SelectCategoryInventoryTileView = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UListView> CategoryInventoryListView = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> InventoryDisplayName = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<URichTextBlock> WeightInformationRichTextBlock = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<URichTextBlock> MoneyInformationRichTextBlock = nullptr;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Inventory Settings")
	TArray<FCategoryInventory> AllCategoryToDivideItems = {FCategoryInventory()};

	void FillSelectCategoryInventoryTileView();

	UPROPERTY(Transient)
	TObjectPtr<class UInventoryComponent> PlayerInventoryComponent = nullptr;
};


