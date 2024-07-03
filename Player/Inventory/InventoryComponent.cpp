// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/Inventory/InventoryComponent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "MedievalDynasty/Player/InteractionMenu/InteractionMenuWidget.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	//FillInventoryWithInitiallItems();
}
/*
void UInventoryComponent::FillInventoryWithInitiallItems()
{
	if (!IsValid(AllItemsDataTable))
		return;

	Inventory.Empty();

	for (const FInitiallInventory& CurrentItem : InitiallInventory)
	{
		FBaseItemData* FoundItem = AllItemsDataTable->FindRow<FBaseItemData>(CurrentItem.ItemRowName, "");
		if (!FoundItem)
			continue;

		FInventoryItem NewInventoryItem = FInventoryItem(CurrentItem.ItemAmount, *FoundItem);
		Inventory.Add(NewInventoryItem);
	}
}*/

void UInventoryComponent::OpenInteractionMenu(int32 SubMenuIDToInitiallyOpen)
{
	const bool bInventoryWasClosed = CloseInventory();
	if (bInventoryWasClosed)
		return;

	if (!IsValid(PlayerController))
		return;

	if (!IsValid(InteractionMenuWidgetClass))
		return;

	InteractionMenuWidget = Cast<UInteractionMenuWidget>(CreateWidget(PlayerController, InteractionMenuWidgetClass));
	if (!IsValid(InteractionMenuWidget))
		return;

	InteractionMenuWidget->AddToViewport();
	InteractionMenuWidget->SetPlayerController(PlayerController);
	InteractionMenuWidget->OpenSubInteractionMenuAccordingToID(SubMenuIDToInitiallyOpen);

	PlayerController->SetShowMouseCursor(true);
	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController, InteractionMenuWidget);

	bIsInventoryOpen = true;
}

bool UInventoryComponent::CloseInventory()
{
	if (!bIsInventoryOpen)
		return false;

	if (IsValid(InteractionMenuWidget))
	{
		InteractionMenuWidget->RemovePreviousSubInteractionWidget();
		InteractionMenuWidget->RemoveFromParent();
	}

	if (IsValid(PlayerController))
	{
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
		PlayerController->SetShowMouseCursor(false);
	}

	bIsInventoryOpen = false;
	return true;
}
