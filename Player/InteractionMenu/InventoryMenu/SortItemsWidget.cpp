// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/SortItemsWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ListView.h"

#include "InventoryMenuWidget.h"
#include "ShowItems/ShowItemDataObject.h"

void USortItemsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SortItemNameButton->OnClicked.AddDynamic(this, &USortItemsWidget::OnClicked_SortItemNameButton);
	SortItemAmountButton->OnClicked.AddDynamic(this, &USortItemsWidget::OnClicked_SortItemAmountButton);
	SortItemWeightButton->OnClicked.AddDynamic(this, &USortItemsWidget::OnClicked_SortItemWeightButton);
	SortItemPriceButton->OnClicked.AddDynamic(this, &USortItemsWidget::OnClicked_SortItemPriceButton);
}

void USortItemsWidget::OnClicked_SortItemNameButton()
{
	if (bSortAscendingItemName)
	{
		auto SortNameLambda = [](const TObjectPtr<UShowItemDataObject>& FirstItem, const TObjectPtr<UShowItemDataObject>& SecondItem)
			{return FirstItem->ItemData.ItemDisplayText.ToString() > SecondItem->ItemData.ItemDisplayText.ToString(); };

		SortItems(SortNameLambda);
	}
	else
	{
		auto SortNameLambda = [](const TObjectPtr<UShowItemDataObject>& FirstItem, const TObjectPtr<UShowItemDataObject>& SecondItem)
			{return FirstItem->ItemData.ItemDisplayText.ToString() < SecondItem->ItemData.ItemDisplayText.ToString(); };

		SortItems(SortNameLambda);
	}

	SortItemNameButton->SetRenderScale(bSortAscendingItemName ? DescendingSortButtonScale : AscendingSortButtonScale);
	bSortAscendingItemName = !bSortAscendingItemName;
}

void USortItemsWidget::OnClicked_SortItemAmountButton()
{
	if (bSortAscendingItemAmount)
	{
		auto SortAmountLambda = [](const TObjectPtr<UShowItemDataObject>& FirstItem, const TObjectPtr<UShowItemDataObject>& SecondItem)
			{return FirstItem->ItemAmount > SecondItem->ItemAmount; };

		SortItems(SortAmountLambda);
	}
	else
	{
		auto SortAmountLambda = [](const TObjectPtr<UShowItemDataObject>& FirstItem, const TObjectPtr<UShowItemDataObject>& SecondItem)
			{return FirstItem->ItemAmount < SecondItem->ItemAmount; };

		SortItems(SortAmountLambda);
	}

	SortItemAmountButton->SetRenderScale(bSortAscendingItemAmount ? DescendingSortButtonScale : AscendingSortButtonScale);
	bSortAscendingItemAmount = !bSortAscendingItemAmount;
}

void USortItemsWidget::OnClicked_SortItemWeightButton()
{
	if (bSortAscendingItemWeight)
	{
		auto SortWeightLambda = [](const TObjectPtr<UShowItemDataObject>& FirstItem, const TObjectPtr<UShowItemDataObject>& SecondItem)
			{return FirstItem->ItemData.ItemWeight* FirstItem->ItemAmount > SecondItem->ItemData.ItemWeight * SecondItem->ItemAmount; };

		SortItems(SortWeightLambda);
	}
	else
	{
		auto SortWeightLambda = [](const TObjectPtr<UShowItemDataObject>& FirstItem, const TObjectPtr<UShowItemDataObject>& SecondItem)
			{return FirstItem->ItemData.ItemWeight* FirstItem->ItemAmount < SecondItem->ItemData.ItemWeight * SecondItem->ItemAmount; };

		SortItems(SortWeightLambda);
	}

	SortItemWeightButton->SetRenderScale(bSortAscendingItemWeight ? DescendingSortButtonScale : AscendingSortButtonScale);
	bSortAscendingItemWeight = !bSortAscendingItemWeight;
}

void USortItemsWidget::OnClicked_SortItemPriceButton()
{
	if (bSortAscendingItemPrice)
	{
		auto SortPriceLambda = [](const TObjectPtr<UShowItemDataObject>& FirstItem, const TObjectPtr<UShowItemDataObject>& SecondItem)
			{return FirstItem->ItemData.ItemPrice > SecondItem->ItemData.ItemPrice; };

		SortItems(SortPriceLambda);
	}
	else
	{
		auto SortPriceLambda = [](const TObjectPtr<UShowItemDataObject>& FirstItem, const TObjectPtr<UShowItemDataObject>& SecondItem)
			{return FirstItem->ItemData.ItemPrice < SecondItem->ItemData.ItemPrice; };

		SortItems(SortPriceLambda);
	}

	SortItemPriceButton->SetRenderScale(bSortAscendingItemPrice ? DescendingSortButtonScale : AscendingSortButtonScale);
	bSortAscendingItemPrice = !bSortAscendingItemPrice;
}

void USortItemsWidget::SortItems(auto LambdaToSortItems)
{
	if (!IsValid(InventoryMenuWidget))
		return;

	TArray<TObjectPtr<UShowItemDataObject>> AllInventoryItems;
	for (TObjectPtr<UObject> CurrentItem : InventoryMenuWidget->GetCategoryInventoryListView()->GetListItems())
	{
		if (!IsValid(CurrentItem))
			continue;

		TObjectPtr<UShowItemDataObject> NewItem = Cast<UShowItemDataObject>(CurrentItem);
		if (!IsValid(NewItem))
			continue;

		AllInventoryItems.Add(NewItem);
	}

	AllInventoryItems.Sort(LambdaToSortItems);
	InventoryMenuWidget->GetCategoryInventoryListView()->SetListItems(AllInventoryItems);
}
