// Fill out your copyright notice in the Description page of Project Settings.


#include "Example/ExampleWorldSettings.h"

#if WITH_EDITOR
void AExampleWorldSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif
