// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/KnowledgeMenu/KnowledgeCategory/CategoryKnowledgeEntry.h"
#include "Components/Button.h"

#include "CategoryKnowledgeEntryObject.h"
#include "MedievalDynasty/Player/InteractionMenu/KnowledgeMenu/KnowledgeWidget.h"

void UCategoryKnowledgeEntry::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SelectCategoryButton->OnClicked.AddDynamic(this, &UCategoryKnowledgeEntry::OnClicked_SelectCategoryButton);
}

void UCategoryKnowledgeEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	if (!IsValid(ListItemObject))
		return;

	CategoryKnowledgeEntryObject = Cast<UCategoryKnowledgeEntryObject>(ListItemObject);
	if (!IsValid(CategoryKnowledgeEntryObject))
		return;

	SelectCategoryButton->SetStyle(CategoryKnowledgeEntryObject->KnowledgeCategory.SelectCategoryButtonStyle);

	if (CategoryKnowledgeEntryObject->bInitialCategory)
		OnClicked_SelectCategoryButton();
}

void UCategoryKnowledgeEntry::OnClicked_SelectCategoryButton()
{
	if (!IsValid(CategoryKnowledgeEntryObject))
		return;

	CategoryKnowledgeEntryObject->KnowledgeWidget->UpdateCategoryDisplayText(CategoryKnowledgeEntryObject->KnowledgeCategory.CategoryDisplayText);
	CategoryKnowledgeEntryObject->KnowledgeWidget->SetDeselectCategoryFunc([this](bool bSelect) {this->ActivateCategoryEntry(bSelect); });
	CategoryKnowledgeEntryObject->KnowledgeWidget->FIllKnowledgeTreeView(CategoryKnowledgeEntryObject);

	ActivateCategoryEntry(true);
}

void UCategoryKnowledgeEntry::ActivateCategoryEntry(bool bActivate)
{
	SelectCategoryButton->SetVisibility(bActivate ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Visible);

	if (!IsValid(CategoryKnowledgeEntryObject))
		return;

	if (bActivate)
	{
		SelectCategoryButton->SetStyle(CategoryKnowledgeEntryObject->KnowledgeCategory.CategorySelectedButtonStyle);
	}
	else
	{
		SelectCategoryButton->SetStyle(CategoryKnowledgeEntryObject->KnowledgeCategory.SelectCategoryButtonStyle);
	}
}