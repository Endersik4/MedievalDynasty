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
}

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

FBaseItemData* UInventoryComponent::GetItemDataFromDataTable(const FName& RowName)
{
	if (!AllItemsDataTable)
		return nullptr;

	return AllItemsDataTable->FindRow<FBaseItemData>(RowName, "");
}
