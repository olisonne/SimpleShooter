// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class SIMPLE_SHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

	void StartFire();

	void StopFire();

	void Shoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	UFUNCTION(BlueprintPure)
	float GetPlayerVelocity() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	UFUNCTION(BlueprintPure)
	float GetCurrentStamina() const;

	UFUNCTION(BlueprintPure)
	bool GetWantToAim() const;

	UFUNCTION(BlueprintPure)
	bool GetIsSprint() const;

	UFUNCTION(BlueprintPure)
	int GetNumberOfBullets() const;

	UFUNCTION(BlueprintPure)
	int GetNumberOfBulletsInStock() const;

	UFUNCTION(BlueprintPure)
	int GetNumberOfAid() const;

	void AddAid();

	void AddBullet(int value);

	UFUNCTION(BlueprintPure)
	bool GetIsRealoading() const;

	void SetObjective(FString Objective);

	UFUNCTION(BlueprintPure)
	FString GetObjective() const;

private:

	UPROPERTY(EditAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UCameraComponent* Camera = nullptr;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UBoxComponent* InteractBox;

	UPROPERTY(EditAnywhere)
	float RotationRate = 50;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
	float Health;

	UPROPERTY(EditAnywhere)
	int NumberOfAid = 3;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY(EditAnywhere)
	float ZoomFOV = 65.5f;

	float DefaultFOV;

	UCharacterMovementComponent* MovementComponent;

	float InitialSpeed;

	UPROPERTY(EditAnywhere)
	float SpeedIncreaser = 2.0f;

	UPROPERTY(EditAnywhere)
	float ZoomInterpSpeed = 20;

	bool bIsSprinting = false;

	UPROPERTY(EditAnywhere)
	float CurrentStamina;

	float MaxStamina = 1.f;

	float StaminaRegenRate = 0.1f;

	bool bWantToAim = false;

	bool bIsReloading = false;

	bool CanShoot = true;

	FString Objective = "Find storage\nmedium in the main room";

	UPROPERTY()
	AGun* Gun;

	class IInteractInterface* Interface = nullptr;

	UFUNCTION()
	void OnBoxBeginOverlap(class UPrimitiveComponent* Comp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBoxEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void OnInteract();
	
	void MoveForward(float AxisValue);

	void MoveRight(float AxisValue);

	void LookUpRate(float AxisValue);

	void LookRightRate(float AxisValue);

	void BeginAim();

	void EndAim();

	void BeginSpring();

	void EndSpring();

	void Healing();

	void Reload();
};
