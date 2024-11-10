// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HeroCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Items/Item.h"
#include "Weapons/Weapons.h"
#include "Animation/AnimMontage.h"

//X = Forward Y = Right Z = Up
//X= Roll Y= Pitch Z= Yaw
	
// Sets default values
AHeroCharacter::AHeroCharacter()
{
	AttackIndex = 0;
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

// this boolean makes you rotate the camera instead of going to engine and change in bp 
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;


	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 300.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	
}

// Called when the game starts or when spawned
void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(HeroMappingContext, 0);
		}
	}
	
}

void AHeroCharacter::Move(const FInputActionValue& Value)
{
	const FVector2d MovementVector = Value.Get<FVector2d>();
// Assigining the the yaw rotation 
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation (0.f, Rotation.Yaw, 0.f);

//to add movement for forward direction 	

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MovementVector.Y);

	const FVector RightdDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightdDirection, MovementVector.X);
}

void AHeroCharacter::Look(const FInputActionValue& Value)
{
// To view the camera with mouse properly we need to add the controller input basically adding the pitch input what
// pitch input will register is written in the code that is Lookaxis vector . Y same for the z which is up and direction 

	const FVector2d LookAxisVector = Value.Get<FVector2d>();
	AddControllerPitchInput(LookAxisVector.Y * MouseSensitivity);
	AddControllerYawInput(LookAxisVector.X * MouseSensitivity);
}



//void AHeroCharacter::ResetCombo()
//{
//	ComboStep = 0; // Reset combo when time expires
//}

void AHeroCharacter::Attack()
{
	if (CanAttack())
	{
		PlayAttackMontage();
		ActionState = EActionState::EAS_Attacking;
	}
}

void AHeroCharacter::AttackEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
}

bool AHeroCharacter::CanAttack()
{
	return ActionState == EActionState::EAS_Unoccupied &&
		   CharacterState != ECharacterState::ECS_Unequipped; 
}

void AHeroCharacter::PlayAttackMontage()
{
	
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
    
	
	
	if (AnimInstance->Montage_IsPlaying(AttackMontage))
	{
		//AnimInstance->Montage_Play(AttackMontage);
		// If the montage is already playing, jump to the next attack section
		FName SectionName = FName(*FString::Printf(TEXT("Attack%d"), AttackIndex + 1));
		AnimInstance->Montage_JumpToSection(SectionName, AttackMontage);

		// Increment the attack index and loop back to 0 after Attack3
		AttackIndex = (AttackIndex + 1) % 3;
	}
	else
	{
		// If no montage is playing, start the attack sequence from the current attack index
		FName SectionName = FName(*FString::Printf(TEXT("Attack%d"), AttackIndex + 1));
		AnimInstance->Montage_Play(AttackMontage);
		AnimInstance->Montage_JumpToSection(SectionName, AttackMontage);

		// Increment the attack index and loop back to 0 after Attack3
		AttackIndex = (AttackIndex + 1) % 3;
	}

	// Debug log to show which attack is being played
	UE_LOG(LogTemp, Warning, TEXT("Playing section: Attack%d"), AttackIndex);

}

void AHeroCharacter::CaptureState()
{
	// Capture the character’s current state and add it to the history array
	FCharacterState NewState;
	NewState.Position = GetActorLocation();
	NewState.Rotation = GetActorRotation();

	// Add new state to the history
	StateHistory.Add(NewState);

	// Maintain only the last 5 seconds of history (e.g., 5 sec at 60 FPS is ~300 frames)
	if (StateHistory.Num() > 300)
	{
		StateHistory.RemoveAt(0);
	}
}

void AHeroCharacter::PerformRewind(float DeltaTime)
{
	if (StateHistory.Num() > 0)
	{
		// Set the character’s position and rotation to the last recorded state
		FCharacterState LastState = StateHistory.Pop();
		SetActorLocation(LastState.Position);
		SetActorRotation(LastState.Rotation);
	}
	else
	{
		// End rewind if history is empty
		bIsRewinding = false;
	}
}

void AHeroCharacter::Jump()
{
	Super::Jump();
}

void AHeroCharacter::Equipping()
{
	AWeapons* OverlappingWeapon = Cast<AWeapons>(OverlappingItem);
	if (OverlappingWeapon)
	{
		OverlappingWeapon->Equip(GetMesh(), FName("RightHandSocket"));
		CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;

		if (OverlappingItem)
		{
			OverlappingItem->SwapMeshOnPickup();
		}
	}
}

void AHeroCharacter::ActivateRewind()
{
	if (!bIsRewinding)
	{
		bIsRewinding = true;
		// Optionally set a timer to stop rewinding after 5 seconds
		GetWorld()->GetTimerManager().SetTimer(RewindTimerHandle, this, &AHeroCharacter::StopRewind, RewindDuration, false);
	}
}

void AHeroCharacter::StopRewind()
{
	bIsRewinding = false;
}

// Called every frame
void AHeroCharacter::Tick(float DeltaTime)
{
	//Override the Tick Function: In the Tick function, capture the state if not rewinding. If rewinding, call PerformRewind().
	Super::Tick(DeltaTime);

	if (bIsRewinding)
	{
		PerformRewind(DeltaTime);
	}
	else
	{
		CaptureState();
	}

}

// Called to bind functionality to input
void AHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHeroCharacter::Move);
		EnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &AHeroCharacter::Look);
	    EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AHeroCharacter::Jump);
		EnhancedInputComponent->BindAction(EquipAction, ETriggerEvent::Triggered, this, &AHeroCharacter::Equipping);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AHeroCharacter::Attack);
		EnhancedInputComponent->BindAction(RewindAction, ETriggerEvent::Triggered, this, &AHeroCharacter::ActivateRewind);
	}

}

