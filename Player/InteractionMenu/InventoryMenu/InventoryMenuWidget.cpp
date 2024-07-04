// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/InventoryMenuWidget.h"
#include "Components/ListView.h"
#include "Components/TileView.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"

#include "MedievalDynasty/Player//Inventory/InventoryComponent.h"
#include "SelectCategory/SelectCategoryEntryObject.h"
#include "ShowItems/ShowItemDataObject.h"
#include "SelectCategory/SelectCategoryInventoryEntry.h"
#include "MedievalDynasty/Player/MedievalPlayer.h"

void UInventoryMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	TObjectPtr<AMedievalPlayer> Player = Cast<AMedievalPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (IsValid(Player))
		PlayerInventoryComponent = Player->GetInventoryComponent();

	FillSelectCategoryInventoryTileView();
	UpdateInventory();
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
			SpawnedSelectCategoryObject->bInitallCategory = true;
		else if (InitiallCategoryType == CurrentSelectCategory.CategoryType)
			SpawnedSelectCategoryObject->bInitallCategory = true;

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

		if (bDivideWithCategory && CurrentItemData->ItemType != CategoryTypeToDivide)
			continue;

		TObjectPtr<UShowItemDataObject> SpawnedShowItemObject = NewObject<UShowItemDataObject>();
		if (!IsValid(SpawnedShowItemObject))
			continue;

		SpawnedShowItemObject->ItemAmount = CurrentItemFromInv.ItemAmount;
		SpawnedShowItemObject->ItemData = *CurrentItemData;
		SpawnedShowItemObject->RowNameToFindItemData = CurrentItemFromInv.ItemRowName;

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
}
