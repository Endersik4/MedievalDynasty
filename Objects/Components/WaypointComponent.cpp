// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Objects/Components/WaypointComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MedievalDynasty/Player/MedievalPlayer.h"

UWaypointComponent::UWaypointComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UWaypointComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
		return;

	TObjectPtr<AMedievalPlayer> Player = Cast<AMedievalPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	if (!IsValid(Player))
		return;

	if (Waypoint.WaypointWorldLocation == FVector(0.f))
		Waypoint.WaypointWorldLocation = GetOwner()->GetActorLocation();

	if (Waypoint.bTrackLocation && !IsValid(Waypoint.ActorToTrack))
	{
		Waypoint.ActorToTrack = GetOwner();
	}

	Player->AddWaypoint(Waypoint);
}
