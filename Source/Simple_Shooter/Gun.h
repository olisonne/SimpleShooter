// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

//class USkeletalMeshComponent;

UCLASS()
class SIMPLE_SHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	int GetNumberOfBulletsInGun() const;

	int GetNumberOfBulletsInStock() const;

	int GetMaxNumberOfBullets() const;

	void Reload();

	UPROPERTY()
	TEnumAsByte<EPhysicalSurface> SurfaceType;

	void AddBullet(int value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSound;

	float RateOfFire = 600;

	float TimeBetweenShots;

	FTimerHandle TimerHandle_TimeBetweenShots;

	float LastFireTime;

	UPROPERTY(EditAnywhere)
	float BaseDamage = 10.f;

	UPROPERTY(EditAnywhere)
	int NumberOfBulletsInGun = 20;

	UPROPERTY(EditAnywhere)
	int MaxNumberOfBulletsInGun = 20;

	UPROPERTY(EditAnywhere)
	int NumberOfBulletsInStock;


	UPROPERTY(EditAnywhere)
	float MaxRange = 10000;

	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);

	AController* GetOwnernCotroller() const;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PullTrigger();

	void StartFire();

	void StopFire();

};
