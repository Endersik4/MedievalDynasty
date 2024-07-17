// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MedievalDynasty/Player/InteractionMenu/MapMenu/WaypointData.h"

#include "WaypointComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MEDIEVALDYNASTY_API UWaypointComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWaypointComponent();

protected:
	virtual void BeginPlay() override;

public:	

private:
	UPROPERTY(EditAnywhere, Category = "Waypoint Settings")
	FWaypoint Waypoint;
		
};
