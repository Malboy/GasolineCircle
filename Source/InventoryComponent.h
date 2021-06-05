// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSwitchWeapon, FAdditionalWeaponInfo, WeaponAdditionalInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAmmoChange, int32, Cout);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GASOLINECIRCLE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	FOnSwitchWeapon OnSwitchWeapon;
	UPROPERTY(BlueprintAssignable, EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		FOnAmmoChange OnAmmoChange;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
		FAmmoSlot AmmoSlots;
	
	bool SwitchWeapon(FAdditionalWeaponInfo Info);

	FAdditionalWeaponInfo GetAdditionalInfoWeapon();
	void SetAdditionalInfoWeapon(FAdditionalWeaponInfo NewInfo);

	void WeaponChangeAmmo(int32 AmmoTaken);
};
