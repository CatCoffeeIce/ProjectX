#pragma once

#include "CoreMinimal.h"
#include "CharacterState.generated.h"

USTRUCT(BlueprintType)
struct FCharacterState
{
	GENERATED_BODY()

public:
	// Properties for character state, accessible from Blueprint
	UPROPERTY(BlueprintReadWrite, Category = "State")
	FVector Position;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	FRotator Rotation;

	// Add any other necessary properties here (e.g., health, velocity)
	UPROPERTY(BlueprintReadWrite, Category = "State")
	float Health;
    
	UPROPERTY(BlueprintReadWrite, Category = "State")
	FVector Velocity;

	// Default constructor
	FCharacterState()
		: Position(FVector::ZeroVector),
		  Rotation(FRotator::ZeroRotator),
		  Health(100.f),
		  Velocity(FVector::ZeroVector)
	{}
};