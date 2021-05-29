// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Types.generated.h"

USTRUCT(BlueprintType)
struct FProjectileInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileSetting")
		TSubclassOf<class AProjectileDefault> Projectile = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileSetting")
		float ProjectileDamage = 20.0f;
};

USTRUCT(BlueprintType)
struct FWeaponInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponSetting")
		float WeaponDamage = 20.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponSetting")
		float RateOfFire = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponSetting")
		FProjectileInfo ProjectileSetting;
		
};

UCLASS()
class GASOLINECIRCLE_API UTypes : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};