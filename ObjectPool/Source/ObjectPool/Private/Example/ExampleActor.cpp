// Fill out your copyright notice in the Description page of Project Settings.


#include "Example/ExampleActor.h"


// Sets default values
AExampleActor::AExampleActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AExampleActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExampleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AExampleActor::OnAllocate()
{
	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
	SetActorTickEnabled(true);
	SetCanBeDamaged(true);
}

void AExampleActor::OnRecycle()
{
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	SetCanBeDamaged(false);
}

