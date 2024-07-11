// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WorldInformationMapWidget.generated.h"

class UTextBlock;
class UWrapBox;
class UImage;
UCLASS()
class MEDIEVALDYNASTY_API UWorldInformationMapWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UHorizontalBox> WorldInformationsHorizontalBox = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UWrapBox> TemperatureWrapBox = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UImage> TemperatureImage = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TemperatureTextBlock = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UWrapBox> CurrentDayWrapBox = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UImage> CurrentDayImage = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentDayTextBlock = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UWrapBox> CurrentSeasonWrapBox = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UImage> CurrentSeasonImage = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentSeasonTextBlock = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UWrapBox>CurrentYearWrapBox = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UImage> CurrentYearImage = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentYearTextBlock = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UWrapBox> CurrentKingWrapBox = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UImage> CurrentKingImage = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentKingTextBlock = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UWrapBox> CurrentRelationsWrapBox = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UImage> CurrentRelationsImage = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class URichTextBlock> CurrentRelationsRichTextBlock = nullptr;

private:
	UPROPERTY(EditDefaultsOnly, Category = "World Informations Settings")
	FText TemperatureDecorationText = FText::FromString(TEXT("°C"));
	UPROPERTY(EditDefaultsOnly, Category = "World Informations Settings")
	FText DayDecorationText = FText::FromString(TEXT("Dzien"));
	UPROPERTY(EditDefaultsOnly, Category = "World Informations Settings")
	FText YearDecorationText = FText::FromString(TEXT("Rok:"));
	UPROPERTY(EditDefaultsOnly, Category = "World Informations Settings|Relations")
	FText OverallRelationsDecorationText = FText::FromString(TEXT("Neutralny"));
	UPROPERTY(EditDefaultsOnly, Category = "World Informations Settings|Relations")
	FText DyplomaticRelationsSign = FText();
	UPROPERTY(EditDefaultsOnly, Category = "World Informations Settings|Relations")
	FText RelationsWithPeopleSign = FText();

	void UpdateWorldInformations();
	void UpdateDayInformation(TObjectPtr<class UMedievalGameInstance> MedievalGameInstance);
	void UpdateRelationsInformation(TObjectPtr<class UMedievalGameInstance> MedievalGameInstance);
};
