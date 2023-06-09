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
		// Apply infinite effects to target
		for (const auto EffectClass : InfiniteGameplayEffectClasses)
		{
			ApplyEffectToTarget(OtherActor, EffectClass);	
		}
	}

	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		for (const auto EffectClass : InstantGameplayEffectClasses)
		{
			ApplyEffectToTarget(OtherActor, EffectClass);	
		}
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		for (const auto EffectClass : DurationGameplayEffectClasses)
		{
			ApplyEffectToTarget(OtherActor, EffectClass);	
		}
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* OtherActor)
{
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		for (const auto EffectClass : InfiniteGameplayEffectClasses)
		{
			ApplyEffectToTarget(OtherActor, EffectClass);	
		}
	}

	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		for (const auto EffectClass : InstantGameplayEffectClasses)
		{
			ApplyEffectToTarget(OtherActor, EffectClass);	
		}
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		for (const auto EffectClass : DurationGameplayEffectClasses)
		{
			ApplyEffectToTarget(OtherActor, EffectClass);	
		}
	}
	
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		for (const auto EffectClass : InfiniteGameplayEffectClasses)
		{
			RemoveEffectFromTarget(OtherActor, EffectClass);	
		}
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
		const FGameplayEffectSpecHandle EffectSpecHandle = TargetAbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);

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

