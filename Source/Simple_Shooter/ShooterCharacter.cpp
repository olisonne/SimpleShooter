// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "Simple_ShooterGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ShooterPlayerController.h"
#include "Components/BoxComponent.h"
#include "Interfaces/InteractInterface.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	InteractBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractBox"));
	InteractBox->SetupAttachment(RootComponent);
}


void AShooterCharacter::StartFire()
{
	if (CanShoot)
	{
		Gun->StartFire();
	}
	
}

void AShooterCharacter::StopFire()
{
	Gun->StopFire();
}

void AShooterCharacter::Shoot()
{
	Gun->PullTrigger();
}

void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	DefaultFOV = Camera->FieldOfView;

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);

	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);

	MovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
	InitialSpeed = MovementComponent->MaxWalkSpeed;

	Health = MaxHealth;
	CurrentStamina = MaxStamina;

	InteractBox->OnComponentBeginOverlap.AddDynamic(this, &AShooterCharacter::OnBoxBeginOverlap);
	InteractBox->OnComponentEndOverlap.AddDynamic(this, &AShooterCharacter::OnBoxEndOverlap);
}

bool AShooterCharacter::IsDead() const
{
	return (Health <= 0);
}

float AShooterCharacter::GetPlayerVelocity() const
{
	return GetVelocity().Size();
}

float AShooterCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float TargetFOV = bWantToAim ? ZoomFOV : DefaultFOV;
	float NewFOV = FMath::FInterpTo(Camera->FieldOfView, TargetFOV, DeltaTime, ZoomInterpSpeed);

	Camera->SetFieldOfView(NewFOV);

	if (bIsSprinting && CurrentStamina > 0.f && GetPlayerVelocity() > 0)
	{
		CurrentStamina = FMath::FInterpConstantTo(CurrentStamina, 0.f, DeltaTime, StaminaRegenRate);
	}
	else if (bIsSprinting && CurrentStamina < 0.1f)
	{
		EndSpring();
	}
	else
	{
		if (CurrentStamina < MaxStamina)
		{
			CurrentStamina = FMath::FInterpConstantTo(CurrentStamina, MaxStamina, DeltaTime, StaminaRegenRate);
		}
	}
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &AShooterCharacter::StartFire);
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Released, this, &AShooterCharacter::StopFire);
	PlayerInputComponent->BindAction(TEXT("Aiming"), IE_Pressed, this, &AShooterCharacter::BeginAim);
	PlayerInputComponent->BindAction(TEXT("Aiming"),IE_Released , this, &AShooterCharacter::EndAim);
	PlayerInputComponent->BindAction(TEXT("Reload"), IE_Pressed, this, &AShooterCharacter::Reload);
	
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &AShooterCharacter::BeginSpring);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &AShooterCharacter::EndSpring);

	PlayerInputComponent->BindAction(TEXT("Healing"), IE_Pressed, this, &AShooterCharacter::Healing);
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &AShooterCharacter::OnInteract);
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	DamageToApply = FMath::Min(Health, DamageAmount);

	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health is equal to %f"), Health);

	if (IsDead())
	{
		if(this == Cast<AShooterCharacter>(UGameplayStatics::GetPlayerPawn(this, 0)))
		{
			ASimple_ShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimple_ShooterGameModeBase>();
			if (GameMode)
			{
				GameMode->EndGame(false);
			}
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageToApply;
}

float AShooterCharacter::GetCurrentStamina() const
{
	return CurrentStamina;
}

bool AShooterCharacter::GetWantToAim() const
{
	return bWantToAim;
}

bool AShooterCharacter::GetIsSprint() const
{
	return bIsSprinting;
}

int AShooterCharacter::GetNumberOfBullets() const
{
	return Gun->GetNumberOfBulletsInGun();
}

int AShooterCharacter::GetNumberOfBulletsInStock() const
{
	return Gun->GetNumberOfBulletsInStock();
}

int AShooterCharacter::GetNumberOfAid() const
{
	return NumberOfAid;
}

void AShooterCharacter::AddAid()
{
	++NumberOfAid;
}

void AShooterCharacter::AddBullet(int value)
{
	Gun->AddBullet(value);
}

bool AShooterCharacter::GetIsRealoading() const
{
	return bIsReloading;
}

void AShooterCharacter::SetObjective(FString NewObjective)
{
	Objective = NewObjective;
}

FString AShooterCharacter::GetObjective() const
{
	return Objective;
}

void AShooterCharacter::OnBoxBeginOverlap(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Interface = Cast<IInteractInterface>(OtherActor);
	UE_LOG(LogTemp, Warning, TEXT("BrginOverlap"));
	if (Interface)
	{
		Interface->ShowInteractWidget();
	}
}

void AShooterCharacter::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Interface)
	{
		Interface->HideInteractWidget();
		Interface = nullptr;
	}
}

void AShooterCharacter::OnInteract()
{
	if (Interface)
	{
		Interface->InteractWithMe();
	}
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::BeginAim()
{
	if (bIsSprinting)
	{
		EndSpring();
	}
	bWantToAim = true;
}

void AShooterCharacter::EndAim()
{
	bWantToAim = false;
}


void AShooterCharacter::BeginSpring()
{
	if (GetPlayerVelocity() > 10 && !bWantToAim)
	{
		bIsSprinting = true;

		MovementComponent->MaxWalkSpeed *= SpeedIncreaser;
	}
}

void AShooterCharacter::EndSpring()
{
	bIsSprinting = false;
	MovementComponent->MaxWalkSpeed = InitialSpeed;
}

void AShooterCharacter::Healing()
{
	if (NumberOfAid > 0 && Health < MaxHealth)
	{
		--NumberOfAid;
		Health += 30;
	}
}

void AShooterCharacter::Reload()
{
	
	if (Gun->GetNumberOfBulletsInStock() > 0 && Gun->GetNumberOfBulletsInGun() < Gun->GetMaxNumberOfBullets())
	{
		CanShoot = false;
		bIsReloading = true;


		FTimerDelegate TimerCallback;
		TimerCallback.BindLambda([&]()
			{
				Gun->Reload();
				bIsReloading = false;
				CanShoot = true;
			});

		FTimerHandle Handle;
		GetWorld()->GetTimerManager().SetTimer(Handle, TimerCallback, 2.6f, false);
	}
	
}

