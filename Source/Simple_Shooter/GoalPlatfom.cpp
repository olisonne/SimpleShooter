// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalPlatfom.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Simple_ShooterGameModeBase.h"
#include "Simple_Shooter/ShooterCharacter.h"

// Sets default values
AGoalPlatfom::AGoalPlatfom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGoalPlatfom::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AGoalPlatfom::OnSphereBeginOverlap);
}

// Called every frame
void AGoalPlatfom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGoalPlatfom::OnSphereBeginOverlap(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AShooterCharacter* Character = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (Character && OtherActor == Character)
	{
		ASimple_ShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimple_ShooterGameModeBase>();
		if (GameMode)
		{
			GameMode->EndGame(true);
		}
	}
}

