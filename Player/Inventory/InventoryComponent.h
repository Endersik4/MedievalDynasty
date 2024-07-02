// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DELEGATE_OneParam(FSelectSubInteractionMenu, int32);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MEDIEVALDYNASTY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	void OpenInteractionMenu(int32 MenuIDToInitiallyOpen = 0);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Interaction Menu")
	TSubclassOf<class UInteractionMenuWidget> InteractionMenuWidgetClass = nullptr;

	UPROPERTY(Transient)
	bool bIsInventoryOpen = false;

	UPROPERTY(Transient)
	TObjectPtr<class UInteractionMenuWidget> InteractionMenuWidget = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	// returns true if inventory was closed
	bool CloseInventory();
};
