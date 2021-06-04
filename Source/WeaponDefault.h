// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "Types.h"
#include "ProjectileDefault.h"
#include "WeaponDefault.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponReloadStart);

UCLASS()
class GASOLINECIRCLE_API AWeaponDefault : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponDefault();

	FOnWeaponReloadStart OnWeaponReloadStart;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
		class USceneComponent* SceneComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
		class USkeletalMeshComponent* SkeletalMeshWeapon = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
		class UStaticMeshComponent* StaticMeshWeapon = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
		class UArrowComponent* ShootLocation = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireLogic")
		FWeaponInfo WeaponSetting;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info")
		FAdditionalWeaponInfo AdditionalWeaponInfo;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FireTick(float DeltaTime);
	void ReloadTick(float DeltaTime);

	void WeaponInit();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireLogic")
		bool WeaponFiring = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireLogic")
		bool WeaponReloading = false;

	UFUNCTION(BlueprintCallable)
		void SetWeaponStateFire(bool bIsFire);

	bool CheckWeaponCanFire();

	FProjectileInfo GetProjectile();

	void Fire();

	UFUNCTION(BlueprintCallable)
		int32 GetWeaponMagazine();

	void WeaponInitReload();
	void WeaponFinishReload();

	float FireTime = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireLogic")
		float ReloadTimer = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireLogic")
		float ReloadTime = 0.0f;

	FVector ShootEndLocation = FVector(0);
};
