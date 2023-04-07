// Copyright Reaper XeS

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()
public:
	AAuraCharacter();
	void InitAbilityActor();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
};
