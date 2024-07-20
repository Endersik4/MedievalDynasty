// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/InteractionMenuWidget.h"
#include "Components/TileView.h"
#include "GameFramework/InputSettings.h"

#include "SubInteractionMenuObject.h"

void UInteractionMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void UInteractionMenuWidget::OpenSubInteractionMenuAccordingToID(int32 MenuIDToInitiallyOpen)
{
	if (MenuIDToInitiallyOpen < 0)
	{
		MenuIDToInitiallyOpen = AllSubInteractionsMenu.Num() - 1;
	}

	InitialSubInteractionMenuID = MenuIDToInitiallyOpen;
	FillSubInteractionsTileView();
}

void UInteractionMenuWidget::FillSubInteractionsTileView()
{
	SubInteractionsMenuTileView->ClearListItems();

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

void UInteractionMenuWidget::SpawnNewSubInteractionWidget(TSubclassOf<UUserWidget> WidgetClassToSpawn)
{
	if (!IsValid(GetOwningPlayer()))
		return;

	RemovePreviousSubInteractionWidget();
	
	CurrentSubInteractionMenu = CreateWidget(GetOwningPlayer(), WidgetClassToSpawn);
	if (!IsValid(CurrentSubInteractionMenu))
		return;

	CurrentSubInteractionMenu->AddToViewport();
}

void UInteractionMenuWidget::RemovePreviousSubInteractionWidget()
{
	if (IsValid(CurrentSubInteractionMenu))
		CurrentSubInteractionMenu->RemoveFromParent();
	if (SubInteractionMenuDisabledFunc)
		SubInteractionMenuDisabledFunc(false);
}