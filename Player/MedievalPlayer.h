// Copyright Adam Bartela.All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MedievalPlayer.generated.h"

UCLASS()
class MEDIEVALDYNASTY_API AMedievalPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMedievalPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Server, Reliable)
	void ServerMove(FVector Direction, float Axis, const FName InputAxisName);

	UFUNCTION(Server, Reliable)
	void ServerSetPlayerRotation(FRotator NewRotation);

	UPROPERTY(ReplicatedUsing = UpdateRotationOnClients)
	FRotator ReplicatedRotation;
	UFUNCTION()
	void UpdateRotationOnClients();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<class UCapsuleComponent> PlayerCapsuleComponent = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<class UStaticMeshComponent> PlayerMesh = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<class USpringArmComponent> SpringArmComponent = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<class UCameraComponent> CameraComponent = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<class UInventoryComponent> InventoryComponent = nullptr;

	UPROPERTY(EditAnywhere, Category = "Player Settings|Movement")
	float MovementSpeed = 80000.f;
	UPROPERTY(EditAnywhere, Category = "Player Settings|Movement")
	float CounterMovementForce = 30.f;
	// When player wants to move forward and right then the forward speed is added to right speed and the player moves faster, this divider prevents this
	UPROPERTY(EditDefaultsOnly, Category = "Player Settings|Movement")
	float ForwardAndRightAtTheSameTimeDivider = 1.3f;
	UPROPERTY(EditDefaultsOnly, Category = "Player Settings|Movement")
	float MeshRotationSpeed = 7.f;
	UPROPERTY(EditDefaultsOnly, Category = "Player Settings|Camera Settings")
	FFloatRange LimitPitchRotation = FFloatRange(-30.f, 30.f);

	void Forward(float Axis);
	void Right(float Axis);
	void ReplicateMove(FVector Direction, float Axis, const FName InputAxisName);
	void Move(FVector Direction, float Axis, const FName InputAxisName);
	FVector CalculateCounterMovement();

	void LookRight(float Axis);
	void LookUp(float Axis);

	void SetPlayerRotation(FRotator NewRotation);
	void RotateMeshTowardsCameraDir(float Delta);
	UPROPERTY(Transient)
	FRotator TargetRotationToRotate = FRotator::ZeroRotator;
	float GetCurrentYawMoveDirection();

	UPROPERTY(Transient)
	TObjectPtr<APlayerController> PlayerController = nullptr;
};
