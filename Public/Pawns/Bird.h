// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "Bird.generated.h"


class UFloatingPawnMovement;
class UCameraComponent;
class USpringArmComponent;
class UInputAction;
class UCapsuleComponent;
class USkeletalMesh;
class UInputMappingContext;
UCLASS()
class PROJECTX_API ABird : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABird();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* BirdMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookInputAction;
	
	void Move(const FInputActionValue& Value);
	void Look (const FInputActionValue& Value);

private:
// How to create hitbox or capsule for ur 3dmodel also declare this as class component so it does not all function at once in other cpp files if added
    UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere)
    USkeletalMeshComponent* BirdMesh;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	// You have add this pointer or pawn wont move or rotate
	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement* FloatingPawnMovement;
};
