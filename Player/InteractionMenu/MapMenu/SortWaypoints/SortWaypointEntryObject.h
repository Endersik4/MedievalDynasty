// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SortWaypointEntryObject.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALDYNASTY_API USortWaypointEntryObject : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	FText WaypointDisplayText = FText();
	UPROPERTY(EditAnywhere)
	TObjectPtr<UTexture2D> WaypointIcon = nullptr;
};
