// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MedievalGameInstance.generated.h"

UENUM(BlueprintType)
enum ESeasonType
{
	EST_Spring UMETA(DisplayName = "Spring"),
	EST_Summer UMETA(DisplayName = "Summer"),
	EST_Autumn UMETA(DisplayName = "Autumn"),
	EST_Winter UMETA(DisplayName = "Winter")
};
	
USTRUCT(BlueprintType)
struct FSeason
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere)
	FText SeasonDisplayText = FText();
	UPROPERTY(EditAnywhere)
	TEnumAsByte<ESeasonType> SeasonType = EST_Spring;

	FSeason()
	{
		SeasonDisplayText = FText();
		SeasonType = EST_Spring;
	}

	FSeason(const FText NewSeasonText, const TEnumAsByte<ESeasonType> NewSeasonType)
	{
		SeasonDisplayText = NewSeasonText;
		SeasonType = NewSeasonType;
	}

	const bool operator==(const TEnumAsByte<ESeasonType>& OtherSeasonType)
	{
		return SeasonType == OtherSeasonType;
	}
};

UCLASS()
class MEDIEVALDYNASTY_API UMedievalGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	FORCEINLINE double GetCurrentTemperature() const { return CurrentTemperature; }
	FORCEINLINE int32 GetCurrentDay() const { return CurrentDay; }
	FORCEINLINE int32 GetCurrentTimeInMinutes() const { return CurrentTimeInMinutes; }
	FORCEINLINE FSeason GetCurrentSeason() const { return CurrentSeason; }
	FORCEINLINE const TArray<FSeason>& GetAllSeasons() const { return AllSeasons; }
	FORCEINLINE int32 GetCurrentYear() const { return CurrentYear; }
	FORCEINLINE FText GetCurrentKing() const { return CurrentKing; }
	FORCEINLINE float GetDyplomaticRelations() const { return DyplomaticRelations; }
	FORCEINLINE float GetRelationsWithPeople() const { return RelationsWithPeople; }

private:
	UPROPERTY(EditDefaultsOnly, Category = "World Informations")
	double CurrentTemperature = -17.5f;
	UPROPERTY(EditDefaultsOnly, Category = "World Informations")
	int32 CurrentDay = 1;
	UPROPERTY(EditDefaultsOnly, Category = "World Informations")
	int32 CurrentTimeInMinutes = 502;
	UPROPERTY(EditDefaultsOnly, Category = "World Informations")
	FSeason CurrentSeason = FSeason(FText::FromString("Wiosna"), EST_Spring);
	UPROPERTY(EditDefaultsOnly, Category = "World Informations")
	TArray<FSeason> AllSeasons = { FSeason(FText::FromString("Wiosna"), EST_Spring), FSeason(FText::FromString("Lato"), EST_Summer),
		FSeason(FText::FromString("Jesien"), EST_Autumn), FSeason(FText::FromString("Zima"), EST_Winter) };
	UPROPERTY(EditDefaultsOnly, Category = "World Informations")
	int32 CurrentYear = 1;
	UPROPERTY(EditDefaultsOnly, Category = "World Informations")
	FText CurrentKing = FText();
	UPROPERTY(EditDefaultsOnly, Category = "World Informations")
	float DyplomaticRelations = 0.f;
	UPROPERTY(EditDefaultsOnly, Category = "World Informations")
	float RelationsWithPeople = 0.f;
};
