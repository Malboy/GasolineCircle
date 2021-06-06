// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthComponent.h"
#include "CharacterHealthComponent.generated.h"

/**
 * 
 */
UCLASS()
class GASOLINECIRCLE_API UCharacterHealthComponent : public UHealthComponent
{
	GENERATED_BODY()


public:

	void ChangeCurrentHealth(float ChangeValue) override;

};
