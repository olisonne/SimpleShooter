// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

int AGun::GetNumberOfBulletsInGun() const
{
	return NumberOfBulletsInGun;
}

int AGun::GetNumberOfBulletsInStock() const
{
	return NumberOfBulletsInStock;
}

int AGun::GetMaxNumberOfBullets() const
{
	return MaxNumberOfBulletsInGun;
}

void AGun::Reload()
{
	float Subtraction = MaxNumberOfBulletsInGun - NumberOfBulletsInGun;
	if (NumberOfBulletsInStock > Subtraction)
	{
		NumberOfBulletsInGun += Subtraction;
		NumberOfBulletsInStock -= Subtraction;
	}
	else
	{
		NumberOfBulletsInGun += NumberOfBulletsInStock;
		NumberOfBulletsInStock = 0;
	}
}

void AGun::AddBullet(int value)
{
	NumberOfBulletsInStock += value;
}

void AGun::BeginPlay()
{
	Super::BeginPlay();
	TimeBetweenShots = 60 / RateOfFire;
}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnernCotroller();
	if (!OwnerController) return false;
	FVector Start;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Start, Rotation);
	ShotDirection = -Rotation.Vector();

	FVector End = Start + Rotation.Vector() * MaxRange;
	
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	Params.bTraceComplex = true;
	Params.bReturnPhysicalMaterial = true;
	return GetWorld()->LineTraceSingleByChannel(Hit, Start, End,
		ECollisionChannel::ECC_GameTraceChannel1, Params);

}

AController* AGun::GetOwnernCotroller() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return nullptr;

	return OwnerPawn->GetController();
}

void AGun::StartFire()
{
	float FirstDelay = FMath::Max(LastFireTime + TimeBetweenShots - GetWorld()->TimeSeconds, 0.0f);

	GetWorldTimerManager().SetTimer(TimerHandle_TimeBetweenShots, this, &AGun::PullTrigger, TimeBetweenShots, true, FirstDelay);
}

void AGun::StopFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_TimeBetweenShots);
}

void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	if (NumberOfBulletsInGun > 0)
	{
		--NumberOfBulletsInGun;
		if (MuzzleFlash)
		{
			UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
		}
		if (MuzzleSound)
		{
			UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));
		}

		FHitResult Hit;
		FVector ShotDirection;
		bool bSuccess = GunTrace(Hit, ShotDirection);
		if (bSuccess && ImpactEffect)
		{
			if (ImpactSound)
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location);
			}
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
			AActor* HitActor = Hit.GetActor();
			if (HitActor)
			{
				SurfaceType = UPhysicalMaterial::DetermineSurfaceType(Hit.PhysMaterial.Get());
				float ActualDamage = BaseDamage;
				if (SurfaceType == SurfaceType1)
				{
					ActualDamage *= 5.f;
				}
				else if (SurfaceType == SurfaceType2)
				{
					ActualDamage *= 3.f;
				}
				FPointDamageEvent DamageEvent(ActualDamage, Hit, ShotDirection, nullptr);
				HitActor->TakeDamage(ActualDamage, DamageEvent, GetOwnernCotroller(), this);
			}
		}

		LastFireTime = GetWorld()->TimeSeconds;
	}
	
}
