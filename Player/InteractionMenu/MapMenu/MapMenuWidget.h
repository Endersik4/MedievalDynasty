// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "MapMenuWidget.generated.h"

class UTextBlock;
UCLASS()
class MEDIEVALDYNASTY_API UMapMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UHorizontalBox> WorldInformationsHorizontalBox = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TemperatureTextBlock = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentDayTextBlock = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentSeasonTextBlock = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentYearTextBlock = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentKingTextBlock = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class URichTextBlock> CurrentRelationsRichTextBlock = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UImage> BackgroundImageForMap = nullptr;

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
