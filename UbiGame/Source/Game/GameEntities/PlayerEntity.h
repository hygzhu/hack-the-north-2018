#pragma once
#include "GameEngine\EntitySystem\Entity.h"
#include "GameEngine\EntitySystem\Components\AnimationComponent.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
#include "Game\GameComponents\PlayerMovementComponent.h"

namespace Game
{			

	class PlayerEntity : public GameEngine::Entity
	{
	public:
		PlayerEntity(int z);
		~PlayerEntity();

		virtual void OnAddToWorld() override;
		virtual void OnRemoveFromWorld() override;
/*
		void RerenderPlayer(int z);*/

	protected:
		GameEngine::SpriteRenderComponent* m_renderComponent;		
		PlayerMovementComponent*	 m_playerMovementComponent;
		GameEngine::AnimationComponent* m_animComponent;
	};
}

