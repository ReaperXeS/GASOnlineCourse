/**
 * Singleton to store all gameplay tags
 * Copyright Reaper XeS
 **/

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

struct FAuraGameplayTags
{
 static const FAuraGameplayTags& Get() { return Instance; }
 static void InitializeNativeGameplayTags();

 FGameplayTag Attributes_Secondary_Armor;
private:
 static FAuraGameplayTags Instance;
};



