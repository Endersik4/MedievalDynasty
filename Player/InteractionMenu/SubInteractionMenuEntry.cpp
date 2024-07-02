// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/SubInteractionMenuEntry.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "SubInteractionMenuEntry.h"
#include "SubInteractionMenuObject.h"

void USubInteractionMenuEntry::NativeOnInitialized()
{
	SubInteractionButton->OnClicked.AddDynamic(this, &USubInteractionMenuEntry::OnClicked_SubInteractionButton);
	SubInteractionButton->OnHovered.AddDynamic(this, &USubInteractionMenuEntry::OnHovered_SubInteractionButton);
	SubInteractionButton->OnUnhovered.AddDynamic(this, &USubInteractionMenuEntry::OnUnhovered_SubInteractionButton);

	OriginalButtonStyle = SubInteractionButton->GetStyle();
	OriginalTextColor = SubInteractionButton->GetColorAndOpacity();
}

void USubInteractionMenuEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	if (!IsValid(ListItemObject))
		return;

	SubInteractionMenuObject = Cast<USubInteractionMenuObject>(ListItemObject);
	SubInteractionMenuObject->AssignedEntryWidget = this;
	if (!IsValid(SubInteractionMenuObject))
		return;

	SubInteractionTextBlock->SetText(SubInteractionMenuObject->SubInteractionMenuType.InteractionMenuName);

	if (!IsValid(SubInteractionMenuObject->InteractionMenuWidget))
		return;

	if (SubInteractionMenuObject->SubInteractionMenuType.SubInteractionMenuID == SubInteractionMenuObject->InteractionMenuWidget->GetSubInteractionMenuIDToOpen())
		OnClicked_SubInteractionButton();
}

void USubInteractionMenuEntry::OnClicked_SubInteractionButton()
{
	if (!IsValid(SubInteractionMenuObject))
		return;

	if (!IsValid(SubInteractionMenuObject->InteractionMenuWidget))
		return;

	SubInteractionMenuObject->InteractionMenuWidget->SpawnNewSubInteractionWidget(SubInteractionMenuObject->SubInteractionMenuType.SubInteractionMenuWidget, this);
	ActivateSubInteractionMenu();
}

void USubInteractionMenuEntry::OnHovered_SubInteractionButton()
{
	if (bIsInUse)
		return;

	PlayAnimationForward(OnHovered_SubInteractionButton_Anim);
}

void USubInteractionMenuEntry::OnUnhovered_SubInteractionButton()
{
	if (bIsInUse)
		return;

	PlayAnimationForward(OnUnhovered_SubInteractionButton_Anim);
}

void USubInteractionMenuEntry::ActivateSubInteractionMenu(bool bActivate)
{
	bIsInUse = bActivate;
	SubInteractionButton->SetVisibility(bActivate ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Visible);

	if (bActivate)
	{
		SubInteractionButton->SetStyle(MenuActivatedButtonStyle);
		SubInteractionTextBlock->SetColorAndOpacity(MenuActivatedTextColor);
	}
	else
	{
		SubInteractionButton->SetStyle(OriginalButtonStyle);
		SubInteractionTextBlock->SetColorAndOpacity(OriginalTextColor);
	}
}
