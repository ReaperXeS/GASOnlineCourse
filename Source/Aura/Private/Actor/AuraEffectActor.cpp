// Copyright Reaper XeS


#include "Actor/AuraEffectActor.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectTypes.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent")));
}

void AAuraEffectActor::OnBeginOverlap(AActor* OtherActor)
{
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(OtherActor, InfiniteGameplayEffectClass);
	}

	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(OtherActor, InstantGameplayEffectClass);
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(OtherActor, DurationGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* OtherActor)
{
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(OtherActor, InfiniteGameplayEffectClass);
	}

	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(OtherActor, InstantGameplayEffectClass);
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(OtherActor, DurationGameplayEffectClass);
	}
	
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		RemoveEffectFromTarget(OtherActor, InfiniteGameplayEffectClass);
	}
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	// Get Ability System Component from Target Actor
	if(UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
	{
		check(GameplayEffectClass);
		// Make effect context
		FGameplayEffectContextHandle EffectContextHandle = TargetAbilitySystemComponent->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);
		
		// Make effect spec
		const FGameplayEffectSpecHandle EffectSpecHandle = TargetAbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);

		// Apply Gameplay Effect to Target Actor
		const FActiveGameplayEffectHandle ActiveEffectHandle = TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
		if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap && EGameplayEffectDurationType::Infinite == EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy)
		{
			// Infinite effect store handle in map
			ActiveEffectHandles.Add(ActiveEffectHandle, TargetAbilitySystemComponent);			
		}
	}
}

void AAuraEffectActor::RemoveEffectFromTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	// Get Ability System Component from Target Actor
	if(UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
	{
		// Find effect handle in map	
		while (const FActiveGameplayEffectHandle* EffectHandle = ActiveEffectHandles.FindKey(TargetAbilitySystemComponent))
		{
			// Remove effect from Target Actor
			TargetAbilitySystemComponent->RemoveActiveGameplayEffect(*EffectHandle, 1);
			// Remove handle from map
			ActiveEffectHandles.Remove(*EffectHandle);
		}
	}
}

