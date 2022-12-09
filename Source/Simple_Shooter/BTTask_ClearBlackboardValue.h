// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ClearBlackboardValue.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLE_SHOOTER_API UBTTask_ClearBlackboardValue : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UBTTask_ClearBlackboardValue()
	{
		NodeName = TEXT("Clear Blackboard Value");
	}
	
protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};


