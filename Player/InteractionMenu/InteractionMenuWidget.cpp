// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/InteractionMenuWidget.h"
#include "Components/BackgroundBlur.h"
#include "Components/Image.h"
#include "Components/TileView.h"

#include "SubInteractionMenuObject.h"
#include "SubInteractionMenuEntry.h"

void UInteractionMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void UInteractionMenuWidget::OpenSubInteractionMenuAccordingToID(int32 MenuIDToInitiallyOpen)
{
	InitialSubInteractionMenuID = MenuIDToInitiallyOpen;
	FillSubInteractionsTileView();
}

void UInteractionMenuWidget::FillSubInteractionsTileView()
{
	for (const FSubInteractionMenuType& CurrentSubMenuType : AllSubInteractionsMenu)
	{
		TObjectPtr<USubInteractionMenuObject> SpawnedTileViewObject = NewObject<USubInteractionMenuObject>();
		if (!IsValid(SpawnedTileViewObject))
			continue;

		SpawnedTileViewObject->SubInteractionMenuType = CurrentSubMenuType;
		SpawnedTileViewObject->InteractionMenuWidget = this;

		SubInteractionsMenuTileView->AddItem(SpawnedTileViewObject);
	}
}

void UInteractionMenuWidget::SpawnNewSubInteractionWidget(TSubclassOf<UUserWidget> WidgetClassToSpawn, TObjectPtr<USubInteractionMenuEntry> SpawnedSubInteractionEntry)
{
	if (!IsValid(PlayerController))
		return;

	RemovePreviousSubInteractionWidget();

	CurrentSubInteractionMenu = CreateWidget(PlayerController, WidgetClassToSpawn);
	if (!IsValid(CurrentSubInteractionMenu))
		return;

	CurrentSubInteractionMenu->AddToViewport();
	CurrentSubInteractionMenuEntry = SpawnedSubInteractionEntry;
}

void UInteractionMenuWidget::RemovePreviousSubInteractionWidget()
{
	if (IsValid(CurrentSubInteractionMenu))
		CurrentSubInteractionMenu->RemoveFromParent();
	if (IsValid(CurrentSubInteractionMenuEntry))
		CurrentSubInteractionMenuEntry->ActivateSubInteractionMenu(false);
}