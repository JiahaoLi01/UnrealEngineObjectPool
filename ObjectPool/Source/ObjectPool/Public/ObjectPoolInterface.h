// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ObjectPoolInterface.generated.h"

UINTERFACE(Blueprintable)
class UReusable : public UInterface
{
	GENERATED_BODY()
};

class OBJECTPOOL_API IReusable
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnAllocate();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnRecycle();
};
