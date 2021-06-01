// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WeaponDefault.h"
#include "Types.h"
#include "GasolineCircleCharacter.generated.h"

UCLASS(Blueprintable)
class AGasolineCircleCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	AGasolineCircleCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* inputComponent) override; //redefenition of function


	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;

public:
	//weapon
	AWeaponDefault* CurrentWeapon = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<AWeaponDefault> InitWeaponClass = nullptr;
	
	UFUNCTION()
		void InputAxisX(float X_value);
	UFUNCTION()
		void InputAxisY(float Y_value);

	float AxisX = 0.0f;
	float AxisY = 0.0f;

	UFUNCTION()
		void MovementTick(float DelatTime);
	UFUNCTION()
		void InitWeapon();
	UFUNCTION(BlueprintCallable)
		AWeaponDefault* GetCurrentWeapon();

	//input
	UFUNCTION(BlueprintCallable)
		void InputAttackPressed();
	UFUNCTION(BlueprintCallable)
		void InputAttackReleased();
	UFUNCTION(BlueprintCallable)
		void TryReloadWeapon();
	UFUNCTION()
		void WeaponReloadStart();
	UFUNCTION(BlueprintNativeEvent)
		void WeaponReloadStart_BP();

	//Functions
	UFUNCTION(BlueprintCallable)
		void AttackCharEvent(bool bIsFiring);
};

