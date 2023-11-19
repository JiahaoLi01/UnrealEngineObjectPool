// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectPool.h"
#include "GameFramework/WorldSettings.h"
#include "ExampleWorldSettings.generated.h"

UCLASS(BlueprintType, Blueprintable)
class OBJECTPOOL_API AExampleWorldSettings : public AWorldSettings
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FObjectPoolConfig> ObjectPoolConfigs;

public:

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
