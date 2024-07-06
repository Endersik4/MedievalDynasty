// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RenderOnlyPlayerActor.generated.h"

UCLASS()
class MEDIEVALDYNASTY_API ARenderOnlyPlayerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARenderOnlyPlayerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CaptureOnlyActor(TObjectPtr<AActor> ActorToCapture);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<USceneComponent> RootSceneComponent = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<class USpringArmComponent> SpringArmComponent = nullptr;	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<class USceneCaptureComponent2D> CaptureOnlyPlayerSceneComponent = nullptr;
};
