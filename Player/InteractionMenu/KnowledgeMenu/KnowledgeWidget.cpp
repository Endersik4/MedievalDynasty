// Copyright Adam Bartela. All Rights Reserved


#include "KnowledgeWidget.h"
#include "Components/TreeView.h"
#include "Components/TileView.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "KnowledgeCategory/CategoryKnowledgeEntryObject.h"
#include "KnowledgeCategory/CategoryKnowledgeEntry.h"
#include "DropDownMenu/DropDownMenuEntryObject.h"

void UKnowledgeWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	FIllKnowledgeCategoriesTileView();
}

void UKnowledgeWidget::FIllKnowledgeCategoriesTileView()
{
	KnowledgeCategoriesTileView->ClearListItems();

	for (const FKnowledgeCategory& CurrentCategory : AllKnowledgeCategories)
	{
		TObjectPtr<UCategoryKnowledgeEntryObject> CategoryKnowledgeObject = NewObject<UCategoryKnowledgeEntryObject>();
		if (!IsValid(CategoryKnowledgeObject))
			return;

		CategoryKnowledgeObject->KnowledgeCategory = CurrentCategory;
		CategoryKnowledgeObject->KnowledgeWidget = this;

		if (CurrentCategory.KnowledgeType == InitalKnowledgeCategoryType)
			CategoryKnowledgeObject->bInitialCategory = true;
		
		KnowledgeCategoriesTileView->AddItem(CategoryKnowledgeObject);
	}
}

void UKnowledgeWidget::UpdateCategoryDisplayText(const FText& NewCategoryDisplayText)
{
	CategoryDisplayName->SetText(NewCategoryDisplayText);
}

void UKnowledgeWidget::UpdateCategory(TObjectPtr<class UCategoryKnowledgeEntry> NewSelectedKnowledgeCategoryEntry)
{
	if (IsValid(SelectedKnowledgeCategoryEntry))
		SelectedKnowledgeCategoryEntry->ActivateCategoryEntry(false);

	SelectedKnowledgeCategoryEntry = NewSelectedKnowledgeCategoryEntry;
}

void UKnowledgeWidget::FIllKnowledgeTreeView(TObjectPtr<class UCategoryKnowledgeEntryObject> CategoryObjectToFillFrom)
{
	if (!IsValid(CategoryObjectToFillFrom))
		return;

	KnowledgeTreeView->ClearListItems();

	for (const FDropDownMenuData& CurrentDropDownMenu : CategoryObjectToFillFrom->KnowledgeCategory.AllKnowledgeDropDownMenu)
	{
		TObjectPtr<UDropDownMenuEntryObject> DropDownMenuKnowledgeObject = NewObject<UDropDownMenuEntryObject>();
		if (!IsValid(DropDownMenuKnowledgeObject))
			return;

		DropDownMenuKnowledgeObject->DropDownMenuData = CurrentDropDownMenu;
		DropDownMenuKnowledgeObject->KnowledgeWidget = this;

		KnowledgeTreeView->AddItem(DropDownMenuKnowledgeObject);
	}
}