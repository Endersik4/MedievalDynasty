// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/MapMenu/MapMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/RichTextBlock.h"

#include "MedievalDynasty/Framework/MedievalGameInstance.h"

void UMapMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UpdateWorldInformations();
}

void UMapMenuWidget::UpdateWorldInformations()
{
	TObjectPtr<UGameInstance> GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (!IsValid(GameInstance))
		return;

	TObjectPtr<UMedievalGameInstance> MedievalGameInstance = Cast<UMedievalGameInstance>(GameInstance);
	if (!IsValid(MedievalGameInstance))
		return;

	FString WorldInformationText = FString();

	if (MedievalGameInstance->GetCurrentTemperature() >= 0.f)
		WorldInformationText += "+";

	WorldInformationText += FString::SanitizeFloat(FMath::RoundValuesToGivenDecimalNumbers(MedievalGameInstance->GetCurrentTemperature(), 1));
	WorldInformationText += TemperatureDecorationText.ToString();
	TemperatureTextBlock->SetText(FText::FromString(WorldInformationText));

	UpdateDayInformation(MedievalGameInstance);

	CurrentSeasonTextBlock->SetText(MedievalGameInstance->GetCurrentSeason().SeasonDisplayText);

	WorldInformationText = YearDecorationText.ToString() + " " + FString::FromInt(MedievalGameInstance->GetCurrentYear());
	CurrentYearTextBlock->SetText(FText::FromString(WorldInformationText));

	CurrentKingTextBlock->SetText(MedievalGameInstance->GetCurrentKing());

	UpdateRelationsInformation(MedievalGameInstance);
}

void UMapMenuWidget::UpdateDayInformation(TObjectPtr<class UMedievalGameInstance> MedievalGameInstance)
{
	FString WorldInformationText = DayDecorationText.ToString() + " ";
	WorldInformationText += FString::FromInt(MedievalGameInstance->GetCurrentDay());
	WorldInformationText += " ";

	int32 Hours = MedievalGameInstance->GetCurrentTimeInMinutes() / 60;
	int32 Minutes = MedievalGameInstance->GetCurrentTimeInMinutes() % 60;
	if (Hours < 10)
		WorldInformationText += "0";
	WorldInformationText += FString::FromInt(Hours) + ":" + FString::FromInt(Minutes);
	CurrentDayTextBlock->SetText(FText::FromString(WorldInformationText));

}

void UMapMenuWidget::UpdateRelationsInformation(TObjectPtr<class UMedievalGameInstance> MedievalGameInstance)
{
	FString WorldInformationText = OverallRelationsDecorationText.ToString() + " (" + DyplomaticRelationsSign.ToString();
	if (MedievalGameInstance->GetDyplomaticRelations() >= 0.f)
		WorldInformationText += "+";

	WorldInformationText += FString::FromInt(FMath::CeilToInt(MedievalGameInstance->GetDyplomaticRelations())) + "%,";
	WorldInformationText += RelationsWithPeopleSign.ToString();
	if (MedievalGameInstance->GetRelationsWithPeople() >= 0.f)
		WorldInformationText += "+";
	WorldInformationText += FString::FromInt(FMath::CeilToInt(MedievalGameInstance->GetRelationsWithPeople())) + "%)";

	CurrentRelationsRichTextBlock->SetText(FText::FromString(WorldInformationText));
}
