// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Weapons.h"
#include "Character/HeroCharacter.h"

void AWeapons::Equip(USceneComponent* InParent, FName InSocketName)
{
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	ItemMesh->AttachToComponent(InParent, TransformRules, InSocketName);
	
}

void AWeapons::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	// How to attach something to the character when the character overlap the item we cast otheractor as herocharacter
	//then in if check we have to use fattachment rules which is enum with option where to attach and last line is the item
	// getting attached to the character we call our character and get its mesh 

	//AHeroCharacter* HeroCharacter = Cast<AHeroCharacter>(OtherActor);

	//if (HeroCharacter)
	//{
	//	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	//	ItemMesh->AttachToComponent(HeroCharacter->GetMesh(), TransformRules, FName("RightHandSocket"));
	//}

}

void AWeapons::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
