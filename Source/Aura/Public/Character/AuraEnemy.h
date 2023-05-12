// Copyright Reaper XeS

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();

	virtual void InitAbilityActorInfo() override;
	
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	/** ICombatInterface */
	virtual int32 GetPlayerLevel() const override;
	/** End ICombatInterface */

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Defaults")
	int32 Level = 1;
};
