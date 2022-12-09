// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "Aid.generated.h"

UCLASS()
class SIMPLE_SHOOTER_API AAid : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InteractWithMe() override;
	virtual void ShowInteractWidget() override;
	virtual void HideInteractWidget() override;

protected:

	UPROPERTY(EditAnywhere)
	USceneComponent* SceneComp;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* InteractWidget;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* TriggerBox;
};
