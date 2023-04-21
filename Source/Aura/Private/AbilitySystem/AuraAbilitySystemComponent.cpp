// Copyright Reaper XeS


#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle)
{
	// Get tags from effect
	FGameplayTagContainer Tags;
	SpecApplied.GetAllAssetTags(Tags);

	// Loop on all tags
	for (const FGameplayTag& Tag : Tags)
	{
		// Check if tag is a message tag
		// if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Message"))))
		// {
			// Get message from tag
			const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());

			// Add on screen message
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, Msg);
		// }
	}
	
	// Add on screen message
	
}
