// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/KnowledgeMenu/DropDownMenu/KnowledgeInformationEntry.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "KnowledgeInformationEntryObject.h"

void UKnowledgeInformationEntry::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	KnowledgeInformationButton->OnClicked.AddDynamic(this, &UKnowledgeInformationEntry::OnClicked_KnowledgeInformationButton);
}

void UKnowledgeInformationEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	if (!IsValid(ListItemObject))
		return;

	KnowledgeInformationEntryObject = Cast<UKnowledgeInformationEntryObject>(ListItemObject);
	if (!IsValid(KnowledgeInformationButton))
		return;

	KnowledgeNameText->SetText(KnowledgeInformationEntryObject->GameKnowledgeDisplayText);
}

void UKnowledgeInformationEntry::OnClicked_KnowledgeInformationButton()
{
}
