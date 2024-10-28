// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HeroAnimInstance.generated.h"

class UCharacterMovementComponent;
class AHeroCharacter;
/**
 * 
 */
UCLASS()
class PROJECTX_API UHeroAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
      virtual void NativeInitializeAnimation() override;
	  virtual  void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
	AHeroCharacter* HeroCharacter;

	// You need charactermovementcomponent to code for the animation
	UPROPERTY(BlueprintReadOnly, Category = Movement)
    UCharacterMovementComponent* HeroCharacterMovementComponent;

	// need to create a variable for about character how many distance they are moving
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float GroundSpeed;
	
};
