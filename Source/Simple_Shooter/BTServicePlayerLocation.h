// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTServicePlayerLocation.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLE_SHOOTER_API UBTServicePlayerLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTServicePlayerLocation();

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
