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

	DropDownMenuButton->OnClicked.AddDynamic(this, &UDropDownMenuEntry::OnClicked_DropDownMenuButton);
}

void UDropDownMenuEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	if (!IsValid(ListItemObject))
		return;

	DropDownMenuEntryObject = Cast<UDropDownMenuEntryObject>(ListItemObject);
	if (!IsValid(DropDownMenuEntryObject))
		return;

	FString NewName = DropDownMenuEntryObject->DropDownMenuData.DropDownMenuName.ToString();
	NewName += " (" + FString::FromInt(DropDownMenuEntryObject->DropDownMenuData.AllKnowledgeInMenuRowNames.Num());
	NewName += ")";
	DropDownMenuNameText->SetText(FText::FromString(NewName));
}

void UDropDownMenuEntry::OnClicked_DropDownMenuButton()
{
	FillKnowledgeInformationsTreeView();
}

void UDropDownMenuEntry::FillKnowledgeInformationsTreeView()
{
	if (!IsValid(DropDownMenuEntryObject))
		return;

	KnowledgeInformationsTreeView->ClearListItems();

	if (DropDownMenuEntryObject->bMenuIsOpened)
	{
		KnowledgeInformationsTreeView->SetVisibility(ESlateVisibility::Collapsed);
		DropDownMenuEntryObject->bMenuIsOpened = false;
		DropDownArrowImage->SetRenderTransformAngle(ArrowAngleWhenClosed);
		return;
	}

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

		KnowledgeInformationEntryObject->GameKnowledgeDisplayText = FoundGameKnowledge->KnowledgeName;
		KnowledgeInformationEntryObject->GameKnowledgeRowName = CurrentKnowledgeRowName;
		KnowledgeInformationEntryObject->KnowledgeWidget = DropDownMenuEntryObject->KnowledgeWidget;

		KnowledgeInformationsTreeView->AddItem(KnowledgeInformationEntryObject);
	}

	DropDownArrowImage->SetRenderTransformAngle(ArrowAngleWhenOpened);
	KnowledgeInformationsTreeView->SetVisibility(ESlateVisibility::Visible);
	DropDownMenuEntryObject->bMenuIsOpened = true;
}

