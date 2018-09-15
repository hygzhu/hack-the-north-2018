#pragma once
#include "GameEngine\EntitySystem\Entity.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"

namespace Game
{

	class ObstacleEntity : public GameEngine::Entity
	{
	public:
		ObstacleEntity(int texture);
		~ObstacleEntity();

		virtual void OnAddToWorld() override;
		virtual void OnRemoveFromWorld() override;

	protected:
		GameEngine::SpriteRenderComponent* m_renderComponent;		
	};
}

