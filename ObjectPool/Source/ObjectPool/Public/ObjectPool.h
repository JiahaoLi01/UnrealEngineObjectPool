// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "ObjectPool.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogObjectPool, Log, All)
DECLARE_STATS_GROUP(TEXT("ObjectPool"), STATGROUP_ObjectPool, STATCAT_Advanced)

class FObjectPoolModule final : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

USTRUCT(BlueprintType)
struct OBJECTPOOL_API FObjectPoolConfig
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Object Pool|Object Pool Config", meta = (MustImplement = "Reusable"))
	TSubclassOf<AActor> ObjectPoolClass{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Object Pool|Object Pool Config")
	int32 PreloadSize{5};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Object Pool|Object Pool Config")
	int32 MaxSize{10};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Object Pool|Object Pool Config")
	bool bAllowAutoReusable{false};
};

UCLASS(Blueprintable, BlueprintType, Within=ObjectPoolSubsystem)
class OBJECTPOOL_API UObjectPool : public UObject
{

	GENERATED_BODY()

	friend class UObjectPoolSubsystem;
public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Object Pool")
	FObjectPoolConfig ObjectPoolConfig;

public:

	static UObjectPool* CreateObjectPool(UObject* Outer, const FObjectPoolConfig& InObjectPoolConfig, bool bUseInterfaceCheck = false);

protected:
	/**
	 * @property UnusedObjects : The push and pop operations of TArray is O(1), so it is used as a stack.
	 */
	UPROPERTY()
	TArray<TObjectPtr<AActor>> UnusedObjects{};

	UPROPERTY()
	TSet<TObjectPtr<AActor>> UsingObjects{};
	
	TQueue<AActor*> AutoReusableObjectQueue{};

protected:

	FORCEINLINE int32 LoadedCount() const {return UnusedObjects.Num() + UsingObjects.Num();}

protected:
	
	AActor* Allocate();
	bool Recycle(AActor* InActor);
	void BreakConnectionsBetweenUsingObjects();
	AActor* ReuseAutoRecycle();

private:

	void LoadObjectsToPreloadSize();
	AActor* CreateObjectInterval() const;

private:
#if WITH_EDITOR
	FORCEINLINE FName GetObjectFolderPath() const {return FName(ObjectPoolConfig.ObjectPoolClass->GetName() + " - ObjectPoolFolder");}
	FORCEINLINE FName GetObjectFolderPath_Unused() const {return FName(ObjectPoolConfig.ObjectPoolClass->GetName() + " - ObjectPoolFolder/Unused");}
	FORCEINLINE FName GetObjectFolderPath_Using() const {return FName(ObjectPoolConfig.ObjectPoolClass->GetName() + " - ObjectPoolFolder/Using");}
#endif
};
