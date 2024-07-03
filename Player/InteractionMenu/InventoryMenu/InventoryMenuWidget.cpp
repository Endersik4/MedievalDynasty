// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/InventoryMenuWidget.h"
#include "Components/ListView.h"
#include "Components/TileView.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

#include "MedievalDynasty/Player//Inventory/InventoryComponent.h"
#include "SelectCategory/SelectCategoryEntryObject.h"
#include "ShowItems/ShowItemDataObject.h"

#include "MedievalDynasty/Player/MedievalPlayer.h"

void UInventoryMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	TObjectPtr<AMedievalPlayer> Player = Cast<AMedievalPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (IsValid(Player))
		PlayerInventoryComponent = Player->GetInventoryComponent();

	FillSelectCategoryInventoryTileView();
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

		SelectCategoryInventoryTileView->AddItem(SpawnedSelectCategoryObject);
	}
}

void UInventoryMenuWidget::UpdateInventory(bool bDivideWithCategory, EItemType CategoryTypeToDivide)
{
	if (!IsValid(PlayerInventoryComponent))
		return;

	CategoryInventoryListView->ClearListItems();

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

		CategoryInventoryListView->AddItem(SpawnedShowItemObject);
	}
}
