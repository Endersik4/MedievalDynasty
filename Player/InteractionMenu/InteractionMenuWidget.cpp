// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/InteractionMenuWidget.h"
#include "Components/TileView.h"

#include "SubInteractionMenuObject.h"

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