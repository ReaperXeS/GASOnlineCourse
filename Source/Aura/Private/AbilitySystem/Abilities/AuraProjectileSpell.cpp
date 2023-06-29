// Copyright Reaper XeS


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"

void UAuraProjectileSpell::SpawnProjectile(const FVector& TargetLocation)
{
	// Spawn the Projectile only on server	
	if (!GetAvatarActorFromActorInfo()->HasAuthority()) return;

	if (const ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		// Set the Projectile Rotation
		FRotator Rotation = (TargetLocation - SocketLocation).Rotation();
		Rotation.Pitch = 0.f; // Parallel to the ground
		SpawnTransform.SetRotation(Rotation.Quaternion());

		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass, SpawnTransform, GetOwningActorFromActorInfo(),Cast<APawn>(GetOwningActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		const UAbilitySystemComponent* SourceAsc = GetAbilitySystemComponentFromActorInfo();
		const FGameplayEffectSpecHandle SpecHandle = SourceAsc->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceAsc->MakeEffectContext());

		const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.MetaTag_Damage, 50.f);
		
		Projectile->DamageEffectSpecHandle = SpecHandle;

		Projectile->FinishSpawning(SpawnTransform);
	}
}

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}
