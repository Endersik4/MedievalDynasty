// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/StatusAndEquipment/Status/PlayerStatusEntry.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "MedievalDynasty/Player/MedievalPlayer.h"
#include "MedievalDynasty/Player/Components/PlayerStatusComponent.h"
#include "PlayerStatusObject.h"

void UPlayerStatusEntry::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UPlayerStatusEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	if (!IsValid(ListItemObject))
		return;

	PlayerStatusObject = Cast<UPlayerStatusObject>(ListItemObject);

	UpdatePlayerStatusEntry();
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
