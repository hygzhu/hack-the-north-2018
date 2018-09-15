#pragma once
#include "GameEngine\EntitySystem\Entity.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"

namespace Game
{

	class ObstacleEntity : public GameEngine::Entity
	{
	public:
		ObstacleEntity(int texture, int _id);
		~ObstacleEntity();

		virtual void OnAddToWorld() override;
		virtual void OnRemoveFromWorld() override;
		void SetBoundingBox(sf::Vector2f size);

	protected:
		GameEngine::SpriteRenderComponent* m_renderComponent;
		GameEngine::CollidableComponent* m_colComponent;
	};
}

