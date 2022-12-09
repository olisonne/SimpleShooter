// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Aid.h"
#include "Kismet/GameplayStatics.h"
#include "WantedInfo.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLE_SHOOTER_API AWantedInfo : public AAid
{
	GENERATED_BODY()
	
	virtual void InteractWithMe() override;
};
