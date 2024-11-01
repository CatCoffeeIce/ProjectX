// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HeroAnimInstance.h"
#include "Character/HeroCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


void UHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
// We are casting the trygetpawnowner to herocharacter class basically giving it the ability of trygetpawnowner

	HeroCharacter = Cast<AHeroCharacter>(TryGetPawnOwner());

// here we are trying to assign the charactermovement function to the movecomponent	

	if (HeroCharacter)
	{
		HeroCharacterMovementComponent = HeroCharacter->GetCharacterMovement();
	}
}

void UHeroAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//Trying to assign the calculation of the speed of character in ground  use that function Ukismet and vsizexy is vector of xy basically

	if (HeroCharacterMovementComponent)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(HeroCharacterMovementComponent->Velocity);
        IsFalling = HeroCharacterMovementComponent->IsFalling();
		CharacterState = HeroCharacter->GetCharacterState();
	}
	
}
