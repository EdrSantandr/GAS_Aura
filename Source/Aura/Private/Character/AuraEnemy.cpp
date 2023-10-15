// Copyright Eder


#include "Character/AuraEnemy.h"
#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
}

void AAuraEnemy::HighlightActor()
{
	//First the Skeletal mesh
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

	//The weapon
	if (Weapon)
	{
		Weapon->SetRenderCustomDepth(true);
		Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	}
}

void AAuraEnemy::UnHighlightActor()
{
	//First the Skeletal mesh
	GetMesh()->SetRenderCustomDepth(false);
	//The weapon
	if (Weapon)
	{
		Weapon->SetRenderCustomDepth(false);
	}
}
