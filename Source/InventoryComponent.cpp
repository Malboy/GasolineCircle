// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	OnSwitchWeapon.Broadcast(AmmoSlots.AdditionalInfo);
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventoryComponent::SwitchWeapon(FAdditionalWeaponInfo Info)
{
	bool bIsSucces = false;
	FAdditionalWeaponInfo NewAdditionalInfo;
	if (!bIsSucces)
	{
		NewAdditionalInfo = AmmoSlots.AdditionalInfo;
		bIsSucces = true;
	}
	
	if (bIsSucces)
	{
		SetAdditionalInfoWeapon(Info);
		OnSwitchWeapon.Broadcast(NewAdditionalInfo);
	}
	return bIsSucces;
}

FAdditionalWeaponInfo UInventoryComponent::GetAdditionalInfoWeapon()
{
	return FAdditionalWeaponInfo();
}

void UInventoryComponent::SetAdditionalInfoWeapon(FAdditionalWeaponInfo NewInfo)
{
	AmmoSlots.AdditionalInfo = NewInfo;
	
}

void UInventoryComponent::WeaponChangeAmmo(int32 AmmoTaken)
{
	AmmoSlots.Cout += AmmoTaken;
	if (AmmoSlots.Cout > AmmoSlots.MaxCout)
	{
		AmmoSlots.Cout = AmmoSlots.MaxCout;
	}
	OnAmmoChange.Broadcast(AmmoSlots.Cout);
}

