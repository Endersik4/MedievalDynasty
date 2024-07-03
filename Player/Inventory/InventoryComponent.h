// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemData.h"
#include "InventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FInitiallInventory
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere)
	int32 ItemAmount = 0;
	UPROPERTY(EditAnywhere)
	FName ItemRowName = FName();
};

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

	FORCEINLINE const TArray<FInitiallInventory>& GetInventory() const { return Inventory; }
	FBaseItemData* GetItemDataFromDataTable(const FName& RowName);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Interaction Menu")
	TSubclassOf<class UInteractionMenuWidget> InteractionMenuWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TObjectPtr<UDataTable> AllItemsDataTable = nullptr;
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TArray<FInitiallInventory> Inventory;
	//UPROPERTY(VisibleAnywhere, Category = "Inventory")
	//TArray<FInventoryItem> Inventory;

	UPROPERTY(Transient)
	bool bIsInventoryOpen = false;

	UPROPERTY(Transient)
	TObjectPtr<class UInteractionMenuWidget> InteractionMenuWidget = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	// returns true if inventory was closed
	bool CloseInventory();

	//void FillInventoryWithInitiallItems();
};
