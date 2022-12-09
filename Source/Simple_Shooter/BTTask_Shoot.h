// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Shoot.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLE_SHOOTER_API UBTTask_Shoot : public UBTTaskNode
{
	GENERATED_BODY()

		UBTTask_Shoot()
	{
		NodeName = "Shoot";
	}


protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
