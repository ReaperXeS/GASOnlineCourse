// Copyright Reaper XeS


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	// Loop on AbilityInputActions and find the one with the same InputTag
	for (const FAuraInputAction& InputAction : AbilityInputActions)
	{
		if (InputAction.InputTag == InputTag)
		{
			return InputAction.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("UAuraInputConfig::FindAbilityInputActionForTag: InputTag %s not found"), *InputTag.ToString());
	}
	return nullptr;
}
