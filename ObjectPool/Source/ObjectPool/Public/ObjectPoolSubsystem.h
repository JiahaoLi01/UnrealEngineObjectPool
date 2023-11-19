// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectPool.h"
#include "Subsystems/WorldSubsystem.h"
#include "ObjectPoolSubsystem.generated.h"

class UObjectPool;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class OBJECTPOOL_API UObjectPoolSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	TMap<TObjectPtr<UClass>, TObjectPtr<UObjectPool>> ObjectPools;

public:

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

public:

	UFUNCTION(BlueprintCallable, Category="Object Pool Subsystem")
	void CreateObjectPool(FObjectPoolConfig ObjectPoolConfig);

	UFUNCTION(BlueprintCallable, Category="Object Pool Subsystem")
	AActor* AllocateByStaticClass(UClass* InClass);

	UFUNCTION(BlueprintCallable, Category="Object Pool Subsystem")
	AActor* AllocateBySubclass(TSubclassOf<AActor> InActorClass);

public:

	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;
};
