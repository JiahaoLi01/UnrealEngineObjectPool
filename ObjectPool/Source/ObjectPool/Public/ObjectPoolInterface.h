// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ObjectPoolInterface.generated.h"

UINTERFACE()
class UReusable : public UInterface
{
	GENERATED_BODY()
};

class OBJECTPOOL_API IReusable
{
	GENERATED_BODY()
public:

	virtual void OnAllocate() = 0;
	virtual void OnRecycle() = 0;
};
