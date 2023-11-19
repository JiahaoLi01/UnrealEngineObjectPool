// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectPoolSubsystem.h"
#include "ExampleObjectPoolSubsystem.generated.h"

UCLASS(BlueprintType, Blueprintable)
class OBJECTPOOL_API UExampleObjectPoolSubsystem : public UObjectPoolSubsystem
{
	GENERATED_BODY()
	
public:

	FORCEINLINE virtual bool ShouldCreateSubsystem(UObject* Outer) const override {return true;}

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
};
