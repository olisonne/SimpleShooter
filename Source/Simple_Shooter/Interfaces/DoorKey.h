// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "Aid.h"
#include "DoorKey.generated.h"

UCLASS()
class SIMPLE_SHOOTER_API ADoorKey : public AAid
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorKey();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OpenDoor();

public:	

	virtual void InteractWithMe();

private:



};