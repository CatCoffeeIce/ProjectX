// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
//#include "ProjectX/DebugMacros.h"
// A macro you can create by #define created a debug sphere macro on project header file ez to spawn multiple if needed
#include "Components/SphereComponent.h"
#include "Character/HeroCharacter.h"



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

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
// to bind the sphere we have to do this binding our sphere with the 2 delegate function 
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AItem::OnSphereEndOverlap);

	if (InitialMesh)
	{
		ItemMesh->SetStaticMesh(InitialMesh);
	}
}


float AItem::TransformedSin()
{
	return Amplitutde* FMath::Sin(RunningTime * TimeConstant);
}

float AItem::TransformedCos()
{
	return Amplitutde* FMath::Cos(RunningTime * TimeConstant);
}

void AItem::SwapMeshOnPickup()
{
	
	if (PickupMesh)
	{
		ItemMesh->SetStaticMesh(PickupMesh);
	}
}

void AItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AHeroCharacter* HeroCharacter = Cast<AHeroCharacter>(OtherActor);
    if (HeroCharacter)
    {
	    HeroCharacter->SetOverlappingItem(this);
    }
}

void AItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AHeroCharacter* HeroCharacter = Cast<AHeroCharacter>(OtherActor);
	if (HeroCharacter)
	{
		HeroCharacter->SetOverlappingItem(nullptr);
	}
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

