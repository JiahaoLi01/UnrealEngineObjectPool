// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectPoolInterface.h"
#include "GameFramework/Actor.h"
#include "ExampleActor.generated.h"

UCLASS(BlueprintType, Blueprintable)
class OBJECTPOOL_API AExampleActor : public AActor, public IReusable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AExampleActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnAllocate_Implementation() override;
	virtual void OnRecycle_Implementation() override;
};
