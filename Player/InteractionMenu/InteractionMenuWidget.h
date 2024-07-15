// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionMenuWidget.generated.h"

USTRUCT(BlueprintType)
struct FSubInteractionMenuType
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere)
	int32 SubInteractionMenuID = 0;
	// Display Name
	UPROPERTY(EditAnywhere)
	FText InteractionMenuName = FText();
	// Widget To spawn when actiaved
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> SubInteractionMenuWidget = nullptr;
};

UCLASS()
class MEDIEVALDYNASTY_API UInteractionMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE int32 GetSubInteractionMenuIDToOpen() const { return InitialSubInteractionMenuID; }

	void OpenSubInteractionMenuAccordingToID(int32 MenuIDToInitiallyOpen);

	void SpawnNewSubInteractionWidget(TSubclassOf<UUserWidget> WidgetClassToSpawn);

	void RemovePreviousSubInteractionWidget();

	TFunction<void(bool)> SubInteractionMenuDisabledFunc;

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UImage> BackgroundImage = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UBackgroundBlur> BackgroundBlur = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UTileView> SubInteractionsMenuTileView = nullptr;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Interaction Menu Settings")
	TArray<FSubInteractionMenuType> AllSubInteractionsMenu;

	UPROPERTY(Transient)
	TObjectPtr<UUserWidget> CurrentSubInteractionMenu = nullptr;

	void FillSubInteractionsTileView();

	UPROPERTY(Transient)
	int32 InitialSubInteractionMenuID = 0;
};
