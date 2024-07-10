// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/KnowledgeMenu/DropDownMenu/KnowledgeInformationEntry.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "KnowledgeInformationEntryObject.h"
#include "MedievalDynasty/Player/InteractionMenu/KnowledgeMenu/DetailedKnowledgeInfoWidget.h"

void UKnowledgeInformationEntry::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	OriginalKnowledgeButtonStyle = KnowledgeInformationButton->GetStyle();
	OriginalKnowledgeFontColor = KnowledgeNameText->GetColorAndOpacity();
	ItemIconImage->SetVisibility(ESlateVisibility::Hidden);

	KnowledgeInformationButton->OnPressed.AddDynamic(this, &UKnowledgeInformationEntry::OnPressed_KnowledgeInformationButton);
}

void UKnowledgeInformationEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	if (!IsValid(ListItemObject))
		return;

	KnowledgeInformationEntryObject = Cast<UKnowledgeInformationEntryObject>(ListItemObject);
	if (!IsValid(KnowledgeInformationButton))
		return;

	SelectedKnowledgeInformationEntry(KnowledgeInformationEntryObject->bKnowledgeSelected);

	KnowledgeNameText->SetText(KnowledgeInformationEntryObject->KnowledgeNameDisplayText);
}

void UKnowledgeInformationEntry::OnPressed_KnowledgeInformationButton()
{
	if (!IsValid(KnowledgeInformationEntryObject))
		return;

	TObjectPtr<UKnowledgeWidget> KnowledgeWidget = KnowledgeInformationEntryObject->KnowledgeWidget;
	if (!IsValid(KnowledgeWidget))
		return;

	KnowledgeWidget->SetDeselectEntryFunc([this](bool bSelect) {this->SelectedKnowledgeInformationEntry(bSelect); });
	SelectedKnowledgeInformationEntry(true);

	KnowledgeWidget->GetDetailedKnowledgeInfoWidget()->UpdateDetailedKnowledgeInformation(KnowledgeInformationEntryObject->KnowledgeRowName, KnowledgeWidget->GetKnowledgeInformationDataAsset());
}

void UKnowledgeInformationEntry::SelectedKnowledgeInformationEntry(bool bSelected)
{
	KnowledgeInformationButton->SetVisibility(bSelected ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Visible);

	if (bSelected)
	{
		KnowledgeInformationButton->SetStyle(SelectedKnowledgeButtonStyle);
		KnowledgeNameText->SetColorAndOpacity(SelectedKnowledgeFontColor);
	}
	else
	{
		KnowledgeInformationButton->SetStyle(OriginalKnowledgeButtonStyle);
		KnowledgeNameText->SetColorAndOpacity(OriginalKnowledgeFontColor);
	}

	if (!IsValid(KnowledgeInformationEntryObject))
		return;

	KnowledgeInformationEntryObject->bKnowledgeSelected = bSelected;
}
