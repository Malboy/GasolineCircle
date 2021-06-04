// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSwitchWeapon, FAdditionalWeaponInfo, WeaponAdditionalInfo);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GASOLINECIRCLE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	FOnSwitchWeapon OnSwitchWeapon;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
		FAmmoSlot AmmoSlots;
	
	FAdditionalWeaponInfo GetAdditionalInfoWeapon();
	void SetAdditionalInfoWeapon(FAdditionalWeaponInfo NewInfo);
};
