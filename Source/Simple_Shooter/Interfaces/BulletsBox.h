// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Aid.h"
#include "BulletsBox.generated.h"

UCLASS()
class SIMPLE_SHOOTER_API ABulletsBox : public AAid
{	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletsBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InteractWithMe() override;

private:

	UPROPERTY(EditDefaultsOnly)
	int value = 10;
};
