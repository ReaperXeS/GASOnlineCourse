// Copyright Reaper XeS


#include "AbilitySystem/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfo(const FGameplayTag& AttributeTag, const bool bLogNotFound) const
{
	// Loop through all AttributeInfos and return the first one that matches the AttributeTag
	for (const FAuraAttributeInfo& AttributeInfo : AttributeInfos)
	{
		if (AttributeInfo.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return AttributeInfo;
		}
	}

	// Log a warning if we didn't find an AttributeInfo
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Warning, TEXT("UAttributeInfo::FindAttributeInfo: Failed to find AttributeInfo for AttributeTag %s"), *AttributeTag.ToString());
	}

	return  FAuraAttributeInfo();
}
