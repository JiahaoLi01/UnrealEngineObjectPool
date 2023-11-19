// Fill out your copyright notice in the Description page of Project Settings.


#include "Example/ExampleObjectPoolSubsystem.h"

#include "Example/ExampleWorldSettings.h"

void UExampleObjectPoolSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	if (AExampleWorldSettings* WorldSettings = Cast<AExampleWorldSettings>(GetWorld()->GetWorldSettings()))
	{
		for (const FObjectPoolConfig ObjectPoolConfig : WorldSettings->ObjectPoolConfigs)
		{
			CreateObjectPool(ObjectPoolConfig);
		}
	}
}
