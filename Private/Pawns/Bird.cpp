// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/Bird.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"


// Sets default values
ABird::ABird()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
    //RootComponent = Capsule or the below both viable we are just setting capsule as root for the 3dmodel
	SetRootComponent(Capsule);

	BirdMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BirdMesh"));
	BirdMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ABird::BeginPlay()
{
	Super::BeginPlay();

	if(APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(BirdMappingContext, 0);
		}
	}
}

void ABird::Move(const FInputActionValue& Value)
{
     const float DirectionValue = Value.Get<float>();
     if (Controller && (DirectionValue != 0.f))
     {
	     FVector Forward = GetActorForwardVector();
     	 AddMovementInput(Forward, DirectionValue);
     }
}

void ABird::Look(const FInputActionValue& Value)
{
     const FVector2D LookAxisValue = Value.Get<FVector2d>();
     if (GetController())
     {
	     AddControllerYawInput(LookAxisValue.X);
     	 AddControllerPitchInput(LookAxisValue.Y);
     }
}

// Called every frame
void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABird::Move);
		EnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &ABird::Look);
    }
}
