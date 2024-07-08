// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/KnowledgeMenu/DropDownMenu/DropDownMenuEntry.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/TreeView.h"
#include "Components/Button.h"

#include "DropDownMenuEntryObject.h"
#include "KnowledgeInformationEntry.h"
#include "KnowledgeInformationEntryObject.h"
#include "MedievalDynasty/Player/InteractionMenu/KnowledgeMenu/KnowledgeWidget.h"

void UDropDownMenuEntry::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	OriginalMenuButtonStyle = SelectMenuButton->GetStyle();
	OriginalMenuFontColor = DropDownMenuNameText->GetColorAndOpacity();

	SelectMenuButton->OnPressed.AddDynamic(this, &UDropDownMenuEntry::OnPressed_SelectMenuButton);
	DropDownMenuButton->OnPressed.AddDynamic(this, &UDropDownMenuEntry::OnPressed_DropDownMenuButton);
}

void UDropDownMenuEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	if (!IsValid(ListItemObject))
		return;

	DropDownMenuEntryObject = Cast<UDropDownMenuEntryObject>(ListItemObject);
	if (!IsValid(DropDownMenuEntryObject))
		return;

	if (DropDownMenuEntryObject->bMenuIsOpened)
	{
		DropDownMenuEntryObject->bMenuIsOpened = false;
		FillKnowledgeInformationsTreeView();
	}
	else
	{
		RestartDropDownMenuEntry();
	}

	SelectedDropDownMenu(DropDownMenuEntryObject->bMenuSelected);

	FString NewDropDownMenuName = DropDownMenuEntryObject->DropDownMenuData.DropDownMenuName.ToString();
	NewDropDownMenuName += " (" + FString::FromInt(DropDownMenuEntryObject->DropDownMenuData.AllKnowledgeInMenuRowNames.Num());
	NewDropDownMenuName += ")";
	DropDownMenuNameText->SetText(FText::FromString(NewDropDownMenuName));
}

void UDropDownMenuEntry::OnPressed_SelectMenuButton()
{
	DropDownMenuEntryObject->KnowledgeWidget->SetDeselectEntryFunc([this](bool bSelect) {this->SelectedDropDownMenu(bSelect); });
	SelectedDropDownMenu(true);
}

void UDropDownMenuEntry::OnPressed_DropDownMenuButton()
{
	OnPressed_SelectMenuButton();

	FillKnowledgeInformationsTreeView();
}

void UDropDownMenuEntry::FillKnowledgeInformationsTreeView()
{
	if (!IsValid(DropDownMenuEntryObject))
		return;

	if (DropDownMenuEntryObject->bMenuIsOpened)
	{
		RestartDropDownMenuEntry();
		return;
	}

	KnowledgeInformationsTreeView->ClearListItems();

	if (!IsValid(DropDownMenuEntryObject->KnowledgeWidget))
		return;

	if (!IsValid(DropDownMenuEntryObject->KnowledgeWidget->GetKnowledgeInformationDataAsset()))
		return;

	for (const FName& CurrentKnowledgeRowName : DropDownMenuEntryObject->DropDownMenuData.AllKnowledgeInMenuRowNames)
	{
		FGameKnowledge* FoundGameKnowledge = DropDownMenuEntryObject->KnowledgeWidget->GetKnowledgeInformationDataAsset()->FindRow<FGameKnowledge>(CurrentKnowledgeRowName, "");
		if (!FoundGameKnowledge)
			return;
	
		TObjectPtr<UKnowledgeInformationEntryObject> KnowledgeInformationEntryObject = NewObject<UKnowledgeInformationEntryObject>();
		if (!IsValid(KnowledgeInformationEntryObject))
			return;

		KnowledgeInformationEntryObject->KnowledgeNameDisplayText = FoundGameKnowledge->KnowledgeName;
		KnowledgeInformationEntryObject->KnowledgeRowName = CurrentKnowledgeRowName;
		KnowledgeInformationEntryObject->KnowledgeWidget = DropDownMenuEntryObject->KnowledgeWidget;

		KnowledgeInformationsTreeView->AddItem(KnowledgeInformationEntryObject);
	}

	DropDownMenuButton->SetRenderTransformAngle(ArrowAngleWhenOpened);
	KnowledgeInformationsTreeView->SetVisibility(ESlateVisibility::Visible);
	DropDownMenuEntryObject->bMenuIsOpened = true;
}

void UDropDownMenuEntry::RestartDropDownMenuEntry()
{
	KnowledgeInformationsTreeView->ClearListItems();

	KnowledgeInformationsTreeView->SetVisibility(ESlateVisibility::Collapsed);
	DropDownMenuEntryObject->bMenuIsOpened = false;
	DropDownMenuButton->SetRenderTransformAngle(ArrowAngleWhenClosed);
}

void UDropDownMenuEntry::SelectedDropDownMenu(bool bSelected)
{
	SelectMenuButton->SetVisibility(bSelected ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Visible);

	if (bSelected)
	{
		SelectMenuButton->SetStyle(SelectedMenuButtonStyle);
		DropDownMenuNameText->SetColorAndOpacity(SelectedMenuFontColor);
	}
	else
	{
		SelectMenuButton->SetStyle(OriginalMenuButtonStyle);
		DropDownMenuNameText->SetColorAndOpacity(OriginalMenuFontColor);
	}

	if (!IsValid(DropDownMenuEntryObject))
		return;

	DropDownMenuEntryObject->bMenuSelected = bSelected;
}

