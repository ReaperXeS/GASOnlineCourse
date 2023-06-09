// Copyright Reaper XeS


#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::AddAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities)
{
	// Loop and Give Ability and active once
	for (auto& Ability : Abilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, 1);
		// if UAuraGameplayAbility then give ability
		if(const UAuraGameplayAbility* AuraAbility = Cast<UAuraGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(AuraAbility->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (InputTag.IsValid())
	{
		// Loop through Activatable Abilities and try to activate to matching tag
		for (FGameplayAbilitySpec& Spec : ActivatableAbilities.Items)
		{
			if (Spec.DynamicAbilityTags.HasTagExact(InputTag))
			{
				AbilitySpecInputPressed(Spec);
				// If not already active, try to activate it
				if (!Spec.IsActive())
				{
					TryActivateAbility(Spec.Handle);
				}
			}
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (InputTag.IsValid())
	{
		// Loop through Activatable Abilities and propagate end Released to matching tag
		for (FGameplayAbilitySpec& Spec : ActivatableAbilities.Items)
		{
			if (Spec.DynamicAbilityTags.HasTagExact(InputTag))
			{
				AbilitySpecInputReleased(Spec);
				// If already active, try to end it
				if (Spec.IsActive())
				{
					AbilitySpecInputReleased(Spec);
				}
			}
		}
	}
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle) const
{
	// Get tags from effect
	FGameplayTagContainer Tags;
	SpecApplied.GetAllAssetTags(Tags);	
	EffectAssetTags.Broadcast(Tags);
}
