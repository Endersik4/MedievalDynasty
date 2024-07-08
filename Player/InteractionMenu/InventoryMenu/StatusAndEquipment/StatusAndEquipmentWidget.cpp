// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu//StatusAndEquipment/StatusAndEquipmentWidget.h"
#include "Components/TileView.h"
#include "Components/TextBlock.h"

#include "Status/PlayerStatusObject.h"
#include "QuickSelect/QuickSelectEntryObject.h"
#include "EquipmentOnPlayer/EquipmentOnPlayerEntryObject.h"
#include "EquipmentOnPlayer/EquipmentOnPlayerEntry.h"
#include "MedievalDynasty/Player/MedievalPlayer.h"
#include "EquipmentOnPlayer/RenderOnlyPlayerActor.h"
#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/InventoryMenuWidget.h"

void UStatusAndEquipmentWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Player = Cast<AMedievalPlayer>(GetOwningPlayerPawn());

	if (IsValid(Player))
	{
		const FString NameAndAgeText = Player->GetPlayersName() + "\r\n" + AgeText.ToString() + FString::FromInt(Player->GetPlayersAge());
		PlayerNameAndAgeTextBlock->SetText(FText::FromString(NameAndAgeText));
	}

	FillPlayerStatusTileView();

	RenderPlayerInWidget();
}

void UStatusAndEquipmentWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (IsValid(SpawnedRenderOnlyPlayer))
		SpawnedRenderOnlyPlayer->Destroy();
}

void UStatusAndEquipmentWidget::FillPlayerStatusTileView()
{
	for (const FStatusEntry& CurrentStatusEntry : StatusEntries)
	{
		TObjectPtr<UPlayerStatusObject> PlayerStatusObject = NewObject<UPlayerStatusObject>();
		if (!IsValid(PlayerStatusObject))
			continue;

		PlayerStatusObject->StatusEntry = CurrentStatusEntry;
		PlayerStatusObject->Player = Player;

		PlayerStatusTileView->AddItem(PlayerStatusObject);
	}
}

void UStatusAndEquipmentWidget::FillWeaponShortcutsTileView()
{
	for (const FQuickToolSelectEntry& CurrentQuickSelectEntry : QuickSelectEntries)
	{
		TObjectPtr<UQuickSelectEntryObject> QuickSelectEntryObject = NewObject<UQuickSelectEntryObject>();
		if (!IsValid(QuickSelectEntryObject))
			continue;

		QuickSelectEntryObject->QuickSelectEntry = CurrentQuickSelectEntry;
		QuickSelectEntryObject->Player = Player;
		QuickSelectEntryObject->InventoryMenuWidget = InventoryMenuWidget;

		WeaponShortcutsTileView->AddItem(QuickSelectEntryObject);
	}
}

void UStatusAndEquipmentWidget::FillEquipmentTileView()
{
	for (const FEquipmentOnPlayer& CurrentEquipment : AllEquipmentsOnPlayer)
	{
		TObjectPtr<UEquipmentOnPlayerEntryObject> EquipmentOnPlayerObject = NewObject<UEquipmentOnPlayerEntryObject>();
		if (!IsValid(EquipmentOnPlayerObject))
			continue;

		EquipmentOnPlayerObject->EquipmentOnPlayer = CurrentEquipment;
		EquipmentOnPlayerObject->Player = Player;
		EquipmentOnPlayerObject->InventoryMenuWidget = InventoryMenuWidget;

		EquipmentTileView->AddItem(EquipmentOnPlayerObject);
	}
}

void UStatusAndEquipmentWidget::RenderPlayerInWidget()
{
	if (!IsValid(RenderOnlyPlayerActorClass))
		return;

	if (!IsValid(Player))
		return;

	FTransform RenderOnlyPlayerTransform = Player->GetActorTransform();
	RenderOnlyPlayerTransform.SetRotation(Player->GetPlayerSkeletalMesh()->GetComponentQuat());

	SpawnedRenderOnlyPlayer = GetWorld()->SpawnActor<ARenderOnlyPlayerActor>(RenderOnlyPlayerActorClass, RenderOnlyPlayerTransform);
	if (!IsValid(SpawnedRenderOnlyPlayer))
		return;

	SpawnedRenderOnlyPlayer->AttachToComponent(Player->GetPlayerSkeletalMesh(), FAttachmentTransformRules::KeepWorldTransform);
	SpawnedRenderOnlyPlayer->CaptureOnlyActor(Player);
}

void UStatusAndEquipmentWidget::HighlightEquipmentOnPlayer(bool bHighlight, const FBaseItemData& ItemToCheck)
{
	if (!bHighlight)
	{
		if (IsValid(HighlightedEquipmentOnPlayer))
			HighlightedEquipmentOnPlayer->HighlightEquipment(false);
		return;
	}

	for (UObject* CurrentItem : EquipmentTileView->GetListItems())
	{
		if (!IsValid(CurrentItem))
			continue;

		TObjectPtr<UEquipmentOnPlayerEntryObject> EquipmentOnPlayerObject = Cast<UEquipmentOnPlayerEntryObject>(CurrentItem);
		if (!IsValid(EquipmentOnPlayerObject))
			continue;

		if (EquipmentOnPlayerObject->EquipmentOnPlayer.CanEquipOnlyEquipmentType != ItemToCheck.EquipmentType)
			continue;

		TObjectPtr<UUserWidget> FoundEntryWidget = EquipmentTileView->GetEntryWidgetFromItem(CurrentItem);
		if (!IsValid(FoundEntryWidget))
			continue;

		HighlightedEquipmentOnPlayer = Cast<UEquipmentOnPlayerEntry>(FoundEntryWidget);
		if (!IsValid(HighlightedEquipmentOnPlayer))
			continue;

		HighlightedEquipmentOnPlayer->HighlightEquipment();
	}
}