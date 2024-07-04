// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/InventoryMenuWidget.h"
#include "Components/ListView.h"
#include "Components/TileView.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"

#include "MedievalDynasty/Player//Inventory/InventoryComponent.h"
#include "SelectCategory/SelectCategoryEntryObject.h"
#include "ShowItems/ShowItemDataObject.h"
#include "SelectCategory/SelectCategoryInventoryEntry.h"
#include "MedievalDynasty/Player/MedievalPlayer.h"
#include "MedievalDynasty/Player/Components/PlayerStatusComponent.h"
#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/DetailedItemInfoWidget.h"

void UInventoryMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	DetailedItemInfoWidget->SetVisibility(ESlateVisibility::Hidden);

	Player = Cast<AMedievalPlayer>(GetOwningPlayerPawn());
	if (IsValid(Player))
		PlayerInventoryComponent = Player->GetInventoryComponent();
	
	FillSelectCategoryInventoryTileView();

	UpdatePlayerStatus();
}

void UInventoryMenuWidget::FillSelectCategoryInventoryTileView()
{
	for (const FCategoryInventory& CurrentSelectCategory : AllCategoryToDivideItems)
	{
		TObjectPtr<USelectCategoryEntryObject> SpawnedSelectCategoryObject = NewObject<USelectCategoryEntryObject>();
		if (!IsValid(SpawnedSelectCategoryObject))
			continue;

		SpawnedSelectCategoryObject->CategoryToDivideItems = CurrentSelectCategory;
		SpawnedSelectCategoryObject->InventoryMenuWidget = this;

		if (!CurrentSelectCategory.bDivideItemsUsingCategory && InitiallCategoryType == EIT_None)
			SpawnedSelectCategoryObject->bInitallySelectedCategory = true;
		else if (InitiallCategoryType == CurrentSelectCategory.CategoryType)
			SpawnedSelectCategoryObject->bInitallySelectedCategory = true;

		SelectCategoryInventoryTileView->AddItem(SpawnedSelectCategoryObject);
	}
}

void UInventoryMenuWidget::UpdateInventory(bool bDivideWithCategory, EItemType CategoryTypeToDivide)
{
	if (!IsValid(PlayerInventoryComponent))
		return;

	CategoryInventoryListView->ClearListItems();
	NoItemsDisplayTextBlock->SetVisibility(ESlateVisibility::HitTestInvisible);

	for (const FInitiallInventory& CurrentItemFromInv : PlayerInventoryComponent->GetInventory())
	{
		FBaseItemData* CurrentItemData = PlayerInventoryComponent->GetItemDataFromDataTable(CurrentItemFromInv.ItemRowName);
		if (!CurrentItemData)
			continue;

		// if player selected category then add only items with that category
		if (bDivideWithCategory && CurrentItemData->ItemType != CategoryTypeToDivide) 
			continue;

		TObjectPtr<UShowItemDataObject> SpawnedShowItemObject = NewObject<UShowItemDataObject>();
		if (!IsValid(SpawnedShowItemObject))
			continue;

		SpawnedShowItemObject->ItemAmount = CurrentItemFromInv.ItemAmount;
		SpawnedShowItemObject->ItemData = *CurrentItemData;
		SpawnedShowItemObject->RowNameToFindItemData = CurrentItemFromInv.ItemRowName;
		SpawnedShowItemObject->InventoryMenuWidget = this;

		// if this is the first item to be added then show detailed information
		if (CategoryInventoryListView->GetNumItems() == 0)
		{
			SpawnedShowItemObject->bInitallySelectedItem = true;
		}

		NoItemsDisplayTextBlock->SetVisibility(ESlateVisibility::Hidden);

		CategoryInventoryListView->AddItem(SpawnedShowItemObject);
	}

}

void UInventoryMenuWidget::UpdateCategoryDisplayText(const FText& NewCategoryDisplayText)
{
	CategoryDisplayName->SetText(NewCategoryDisplayText);
}

void UInventoryMenuWidget::UpdateCategory(TObjectPtr<class USelectCategoryInventoryEntry> NewCurrentSelectedCategoryEntry)
{
	if (IsValid(CurrentSelectedCategoryEntry))
		CurrentSelectedCategoryEntry->ActivateCategoryEntry(false);

	CurrentSelectedCategoryEntry = NewCurrentSelectedCategoryEntry;

	DetailedItemInfoWidget->SetVisibility(ESlateVisibility::Hidden);
}

void UInventoryMenuWidget::UpdatePlayerStatus()
{
	if (!IsValid(Player))
		return;

	TObjectPtr<UPlayerStatusComponent> PlayerStatusComponent = Player->GetPlayerStatusComponent();
	if (!IsValid(PlayerStatusComponent))
		return;

	PlayerStatusComponent->RefreshWeightValue();

	const FString MoneyValue = FString::SanitizeFloat(PlayerStatusComponent->GetStatusValue(EST_Money), 0);
	MoneyDisplayTextBlock->SetText(FText::FromString(MoneyValue));

	const FString WeightInformation = FString::SanitizeFloat(PlayerStatusComponent->GetStatusValue(EST_Weight)) + " / "
		+ FString::SanitizeFloat(PlayerStatusComponent->GetStatusMaxValue(EST_Weight), 2) + " kg";
	WeightDisplayTextBlock->SetText(FText::FromString(WeightInformation));
}

#pragma region /////////// DETAILED INFORMATION ABOUT ITEM ///////////////
void UInventoryMenuWidget::OnClicked_ShowItemDataEntry(UShowItemDataObject* ClickedShowItemDataObject)
{
	if (!IsValid(ClickedShowItemDataObject))
		return;

	DetailedItemInfoWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
	DetailedItemInfoWidget->UpdateItemInformation(&ClickedShowItemDataObject->ItemData);
}
#pragma endregion