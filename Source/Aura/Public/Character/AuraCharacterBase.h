// Copyright Reaper XeS

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

/************************/
/* Forward declarations	*/
/************************/
class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayAbility;
class UAnimMontage;
class UMaterialInstance;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraCharacterBase();

	virtual void InitAbilityActorInfo();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Aura|Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Aura|Attributes")
	TSubclassOf<class UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Aura|Attributes")
	TSubclassOf<class UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Aura|Attributes")
	TSubclassOf<class UGameplayEffect> DefaultVitalAttributes;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffect, float Level) const;
	virtual void InitializeDefaultAttributes() const;

	void AddStartupAbilities() const;

	UPROPERTY(EditAnywhere, Category = "Aura|Combat")
	FName WeaponTipSocketName = "WeaponTipSocket";


	/**** Combat Interface ****/
	virtual FVector GetCombatSocketLocation() const override;

	virtual UAnimMontage* GetHitReactMontage_Implementation() override;

	virtual void Die();
	/**** End Combat Interface ****/

	UFUNCTION(NetMulticast, Reliable)
	virtual void MultiCastHandleDeath();

	UPROPERTY(EditAnywhere, Category = "Aura|Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;

 	/** Dissolve Effects **/
	void Dissolve();

	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveMeshTimeLine(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveWeaponTimeLine(UMaterialInstanceDynamic* DynamicMaterialInstance);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> MeshDissolveMaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterialInstance;
private:
	UPROPERTY(EditAnywhere, Category = "Aura|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
};
