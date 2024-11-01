// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Character/CharacterType.h"
#include "Character/CharacterState.h"
#include "HeroCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class AItem;


UCLASS()
class PROJECTX_API AHeroCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHeroCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Jump() override;

	void Equipping();

	// Activate rewind
	void ActivateRewind();

	// Stop rewind
	void StopRewind();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* HeroMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LookInputAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* EquipAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* RewindAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	float MouseSensitivity = 1.0f;

	// Timer handle for the rewind timer
	FTimerHandle RewindTimerHandle;  // Add this line

	

private:

	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	// Making a pointer for the item so we can use the item class abilites when the herocharacter interacts with it
	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;

	// Stores the last 5 seconds of character states
	TArray<FCharacterState>StateHistory;

	// Rewind duration
	float RewindDuration = 5.0f;

	// Whether the rewind is active
	bool bIsRewinding = false;

	// Function to capture current state
	void CaptureState();

	// Function to perform rewind
	void PerformRewind(float DeltaTime);

public:
	FORCEINLINE void SetOverlappingItem(AItem* Item) {OverlappingItem = Item;}
	FORCEINLINE ECharacterState GetCharacterState() const{return CharacterState; }
	
	
};
