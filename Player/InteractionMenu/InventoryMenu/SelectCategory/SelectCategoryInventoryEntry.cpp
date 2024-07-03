// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/SelectCategory/SelectCategoryInventoryEntry.h"
#include "Components/Button.h"

#include "SelectCategoryEntryObject.h"
#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/InventoryMenuWidget.h"

void USelectCategoryInventoryEntry::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SelectCategoryButton->OnClicked.AddDynamic(this, &USelectCategoryInventoryEntry::OnClicked_SortInventoryButton);
}

void USelectCategoryInventoryEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	if (!IsValid(ListItemObject))
		return;

	SelectCategoryEntryObject = Cast<USelectCategoryEntryObject>(ListItemObject);
	if (!IsValid(SelectCategoryEntryObject))
		return;

	SelectCategoryButton->SetStyle(SelectCategoryEntryObject->CategoryToDivideItems.SelectCategoryButtonStyle);
}

void USelectCategoryInventoryEntry::OnClicked_SortInventoryButton()
{
	if (!IsValid(SelectCategoryEntryObject))
		return;

	SelectCategoryEntryObject->InventoryMenuWidget->UpdateInventory(SelectCategoryEntryObject->CategoryToDivideItems.bDivideItemsUsingCategory, SelectCategoryEntryObject->CategoryToDivideItems.CategoryType);

}
