// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickableItem.generated.h"

UCLASS()
class MEDIEVALDYNASTY_API APickableItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickableItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ItemMeshComponent;

};
