// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalPlatform.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Simple_ShooterGameModeBase.h"
#include "ShooterCharacter.h"

// Sets default values
AGoalPlatform::AGoalPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGoalPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AGoalPlatform::OnShpereBeginOverlap);
}

// Called every frame
void AGoalPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGoalPlatform::OnShpereBeginOverlap(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

