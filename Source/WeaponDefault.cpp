// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponDefault.h"

// Sets default values
AWeaponDefault::AWeaponDefault()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneComponent;

	SkeletalMeshWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	SkeletalMeshWeapon->SetGenerateOverlapEvents(false);
	SkeletalMeshWeapon->SetCollisionProfileName(TEXT("NoCollision"));
	SkeletalMeshWeapon->SetupAttachment(RootComponent);

	StaticMeshWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMeshWeapon->SetGenerateOverlapEvents(false);
	StaticMeshWeapon->SetCollisionProfileName(TEXT("NoCollision"));
	StaticMeshWeapon->SetupAttachment(RootComponent);

	ShootLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Component"));
	ShootLocation->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWeaponDefault::BeginPlay()
{
	Super::BeginPlay();
	
	WeaponInit();
}

// Called every frame
void AWeaponDefault::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FireTick(DeltaTime);
	ReloadTick(DeltaTime);
}

void AWeaponDefault::FireTick(float DeltaTime)
{
	if (GetWeaponMagazine() > 0)
	{
		if (WeaponFiring)
			if (FireTime < 0.0f)
			{
				if (!WeaponReloading)
				{
					Fire();
				}
			}
			else
				FireTime -= DeltaTime;
	}
	else
	{
		if (!WeaponReloading)
		{
			WeaponInitReload();
		}
	}
}

void AWeaponDefault::ReloadTick(float DeltaTime)
{
	if (WeaponReloading)
	{
		if (ReloadTimer < 0.0f)
		{
			WeaponFinishReload();
		}
		else
		{
			ReloadTimer -= DeltaTime;
		}
	}
}

void AWeaponDefault::WeaponInit()
{
	if (SkeletalMeshWeapon && !SkeletalMeshWeapon->SkeletalMesh)
	{
		SkeletalMeshWeapon->DestroyComponent();
	}

	if (StaticMeshWeapon && !StaticMeshWeapon->GetStaticMesh())
	{
		StaticMeshWeapon->DestroyComponent();
	}

	//WeaponSetting.Magazine = WeaponSetting.MaxMagazine;
	//ReloadTime = WeaponSetting.ReloadTime;
}


	void AWeaponDefault::SetWeaponStateFire(bool bIsFire)
	{
		if (CheckWeaponCanFire())
			WeaponFiring = bIsFire;
		else
			WeaponFiring = false;
	}

	bool AWeaponDefault::CheckWeaponCanFire()
{
	return true;
}

FProjectileInfo AWeaponDefault::GetProjectile()
{
	return WeaponSetting.ProjectileSetting;
}

void AWeaponDefault::Fire()
{
	FireTime = WeaponSetting.RateOfFire;
	AdditionalWeaponInfo.Round = AdditionalWeaponInfo.Round - 1;

	if (ShootLocation)
	{
		FVector SpawnLoc = ShootLocation->GetComponentLocation();
		FRotator SpawnRot = ShootLocation->GetComponentRotation();
		FProjectileInfo ProjectileInfo;
		ProjectileInfo = GetProjectile();

		FVector Dir = ShootEndLocation - SpawnLoc;
		Dir.Normalize();

		FMatrix myMatrix(Dir, FVector(0, 1, 0), FVector(0, 0, 1), FVector::ZeroVector);
		SpawnRot = myMatrix.Rotator();

		if (ProjectileInfo.Projectile)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			SpawnParams.Owner = GetOwner();
			SpawnParams.Instigator = GetInstigator();

			AProjectileDefault* myProjectile = Cast<AProjectileDefault>(GetWorld()->SpawnActor(ProjectileInfo.Projectile, &SpawnLoc, &SpawnRot, SpawnParams));
			if (myProjectile)
			{
				myProjectile->InitProjectile(WeaponSetting.ProjectileSetting);
				//myProjectile->InitialLifeSpan = 20.0f;
			}
		}
	}
}

int32 AWeaponDefault::GetWeaponMagazine()
{
	return AdditionalWeaponInfo.Round;
}

void AWeaponDefault::WeaponInitReload()
{
	WeaponReloading = true;

	ReloadTimer = WeaponSetting.ReloadTime;
	OnWeaponReloadStart.Broadcast();
}

void AWeaponDefault::WeaponFinishReload()
{
	WeaponReloading = false;
	int32 AmmoNeedTake = AdditionalWeaponInfo.Round;
	AmmoNeedTake = AmmoNeedTake - WeaponSetting.MaxMagazine;
	AdditionalWeaponInfo.Round = WeaponSetting.MaxMagazine;

	OnWeaponReloadEnd.Broadcast(true, AmmoNeedTake);
}
