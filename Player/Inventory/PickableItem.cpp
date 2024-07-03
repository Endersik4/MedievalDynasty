// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/Inventory/PickableItem.h"
#include "Components/StaticMeshComponent.h"

APickableItem::APickableItem()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh Component"));
	RootComponent = ItemMeshComponent;
	ItemMeshComponent->SetSimulatePhysics(true);
}

void APickableItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

