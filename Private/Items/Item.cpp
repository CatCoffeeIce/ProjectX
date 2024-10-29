// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
//#include "ProjectX/DebugMacros.h"
// A macro you can create by #define created a debug sphere macro on project header file ez to spawn multiple if needed
#include "Components/SphereComponent.h"
#include "ProjectX/ProjectX.h"


// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	RootComponent = ItemMesh;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());

}


float AItem::TransformedSin()
{
	return Amplitutde* FMath::Sin(RunningTime * TimeConstant);
}

float AItem::TransformedCos()
{
	return Amplitutde* FMath::Cos(RunningTime * TimeConstant);
}
// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime = RunningTime + DeltaTime;

	//float DeltaZ = Amplitutde* FMath::Sin(RunningTime * TimeConstant);

    //AddActorWorldOffset(FVector(0.f, 0.f, DeltaZ));

    //DRAW_SINGLE_SPHERE(GetActorLocation());
	//DRAW_SINGLE_VECTOR(GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100.f);
}

