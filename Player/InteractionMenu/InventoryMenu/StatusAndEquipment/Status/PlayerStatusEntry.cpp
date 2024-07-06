// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/StatusAndEquipment/Status/PlayerStatusEntry.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#include "MedievalDynasty/Player/MedievalPlayer.h"
#include "MedievalDynasty/Player/Components/PlayerStatusComponent.h"
#include "PlayerStatusObject.h"

void UPlayerStatusEntry::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	HoverStatusBorder->SetVisibility(ESlateVisibility::Hidden);

	HoverStatusButton->OnHovered.AddDynamic(this, &UPlayerStatusEntry::OnHovered_HoverStatusBorder);
	HoverStatusButton->OnUnhovered.AddDynamic(this, &UPlayerStatusEntry::OnUnhovered_HoverStatusBorder);
}

void UPlayerStatusEntry::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::Tick(MyGeometry, DeltaTime);

	MoveHoverStatus(MyGeometry);
}

void UPlayerStatusEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	if (!IsValid(ListItemObject))
		return;

	PlayerStatusObject = Cast<UPlayerStatusObject>(ListItemObject);
	if (!IsValid(PlayerStatusObject))
		return;

	UpdatePlayerStatusEntry();

	HoverStatusTextBlock->SetText(PlayerStatusObject->StatusEntry.StatusEntryDisplayName);
}

void UPlayerStatusEntry::UpdatePlayerStatusEntry()
{
	if (!IsValid(PlayerStatusObject))
		return;

	const FStatusEntry& PlayerStatusEntry = PlayerStatusObject->StatusEntry;

	if (IsValid(PlayerStatusEntry.StatusIconTexture))
		StatusIcon->SetBrushFromTexture(PlayerStatusEntry.StatusIconTexture);

	StatusProgressBar->SetWidgetStyle(PlayerStatusEntry.StatusProgressBarStyle);

	if (!IsValid(PlayerStatusObject->Player))
		return;

	TObjectPtr<UPlayerStatusComponent> PlayerStatusComponent = PlayerStatusObject->Player->GetPlayerStatusComponent();

	double StatusValue = PlayerStatusComponent->GetStatusValue(PlayerStatusEntry.StatusType);

	if (PlayerStatusEntry.StatusValueType == ESVT_Max)
	{
		StatusProgressBar->SetPercent(StatusValue / PlayerStatusComponent->GetStatusMaxValue(PlayerStatusEntry.StatusType));
		StatusValue = FMath::RoundValuesToGivenDecimalNumbers(StatusValue, 1);
		const FString Value = FString::SanitizeFloat(StatusValue, 0) + "/" + FString::SanitizeFloat(PlayerStatusComponent->GetStatusMaxValue(PlayerStatusEntry.StatusType), 0);
		StatusValueText->SetText(FText::FromString(Value));
	}
	else
	{
		StatusProgressBar->SetPercent(StatusValue);

		if (PlayerStatusEntry.StatusValueType == ESVT_Percent)
		{
			StatusValue = FMath::RoundValuesToGivenDecimalNumbers(StatusValue * 100.f, 0);
		}

		FString Value = FString::SanitizeFloat(StatusValue, 0);
		if (PlayerStatusEntry.StatusValueType == ESVT_Percent)
			Value += "%";
		else if (PlayerStatusEntry.StatusValueType == ESVT_Temperature)
			Value += "C";

		StatusValueText->SetText(FText::FromString(Value));
	}
}

#pragma region ////////// Hover Status /////////////
void UPlayerStatusEntry::OnHovered_HoverStatusBorder()
{
	bStatusHovered = true;
	HoverStatusBorder->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UPlayerStatusEntry::OnUnhovered_HoverStatusBorder()
{
	bStatusHovered = false;
	HoverStatusBorder->SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerStatusEntry::MoveHoverStatus(const FGeometry& MyGeometry)
{
	if (!bStatusHovered)
		return;

	HoverStatusBorder->SetRenderTranslation(MyGeometry.AbsoluteToLocal(UWidgetLayoutLibrary::GetMousePositionOnPlatform()));
}
#pragma endregion