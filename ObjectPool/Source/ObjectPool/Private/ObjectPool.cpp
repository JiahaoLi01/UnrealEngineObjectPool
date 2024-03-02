// Copyright Epic Games, Inc. All Rights Reserved.

#include "ObjectPool.h"

#include "ObjectPoolInterface.h"

#define LOCTEXT_NAMESPACE "FObjectPoolModule"

DEFINE_LOG_CATEGORY(LogObjectPool)

void FObjectPoolModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FObjectPoolModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

UObjectPool* UObjectPool::CreateObjectPool(UObject* Outer, const FObjectPoolConfig& InObjectPoolConfig, bool bUseInterfaceCheck)
{
	UObjectPool* PoolObject = NewObject<UObjectPool>(Outer, StaticClass());
	PoolObject->ObjectPoolConfig = InObjectPoolConfig;

	if (bUseInterfaceCheck)
	{
		check(InObjectPoolConfig.ObjectPoolClass->ImplementsInterface(UReusable::StaticClass()))
	}

	PoolObject->LoadObjectsToPreloadSize();
	return PoolObject;
}

AActor* UObjectPool::Allocate()
{
	AActor* SpawnedActor{nullptr};

	if (UnusedObjects.Num() > 0)
	{
		SpawnedActor = UnusedObjects.Pop();
	}
	else if (LoadedCount() <= ObjectPoolConfig.MaxSize)
	{
		SpawnedActor = CreateObjectInterval();
	}
	else if (ObjectPoolConfig.bAllowAutoReusable)
	{
		SpawnedActor = ReuseAutoRecycle();
	}

	if (SpawnedActor != nullptr)
	{
		UsingObjects.Add(SpawnedActor);
		if (ObjectPoolConfig.bAllowAutoReusable)
		{
			AutoReusableObjectQueue.Enqueue(SpawnedActor);
		}

		if (SpawnedActor->Implements<UReusable>())
		{
			IReusable::Execute_OnAllocate(SpawnedActor);
		}
	}

#if WITH_EDITOR
	SpawnedActor->SetFolderPath(GetObjectFolderPath_Using());
#endif

	UE_LOG(LogObjectPool, Log, TEXT("Spawned an actor from the object pool"))
	return SpawnedActor;
}

bool UObjectPool::Recycle(AActor* InActor)
{
	if (InActor != nullptr && UsingObjects.Contains(InActor))
	{
		UsingObjects.Remove(InActor);
		UnusedObjects.Push(InActor);

#if WITH_EDITOR
		InActor->SetFolderPath(GetObjectFolderPath_Unused());
#endif

		if (InActor->Implements<UReusable>())
		{
			IReusable::Execute_OnRecycle(InActor);
		}

		return true;
	}

	return false;
}

void UObjectPool::BreakConnectionsBetweenUsingObjects()
{
	UsingObjects.Empty();
}

AActor* UObjectPool::ReuseAutoRecycle()
{
	if (UsingObjects.Num() > 0)
	{
		AActor* TargetActor{nullptr};

		while (!AutoReusableObjectQueue.IsEmpty())
		{
			AActor* CandidateObject{nullptr};
			AutoReusableObjectQueue.Dequeue(CandidateObject);
			if (UsingObjects.Contains(CandidateObject))
			{
				TargetActor = CandidateObject;
				break;
			}
		}

		if (TargetActor == nullptr)
		{
			UE_LOG(LogObjectPool, Error, TEXT("%s object pool has no valid object"), *ObjectPoolConfig.ObjectPoolClass->GetName())
			return nullptr;
		}

		UsingObjects.Remove(TargetActor);

		if (TargetActor->Implements<UReusable>())
		{
			IReusable::Execute_OnRecycle(TargetActor);
		}

		return TargetActor;
	}
	return nullptr;
}

void UObjectPool::LoadObjectsToPreloadSize()
{
	const int32 ActualSize = ObjectPoolConfig.PreloadSize - UsingObjects.Num();

	for (TArray<AActor*>::SizeType i = UnusedObjects.Num(); i < ActualSize; ++i)
	{
		AActor* SpawnedActor = CreateObjectInterval();
		UnusedObjects.Push(SpawnedActor);

		if (!ObjectPoolConfig.bRecycleWhenSpawned)
		{
			return;
		}

		if (SpawnedActor->Implements<UReusable>())
		{
			IReusable::Execute_OnRecycle(SpawnedActor);
		}
	}
}

AActor* UObjectPool::CreateObjectInterval() const
{
	AActor* SpawnedActor = GetOuter()->GetWorld()->SpawnActor(ObjectPoolConfig.ObjectPoolClass);
	
#if WITH_EDITOR
	SpawnedActor->SetFolderPath(GetObjectFolderPath_Unused());
#endif
	
	return SpawnedActor;


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FObjectPoolModule, ObjectPool)