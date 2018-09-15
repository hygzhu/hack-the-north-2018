#include "ObstacleEntity.h"

#include "GameEngine/EntitySystem/Components/CollidableComponent.h"

#include <SFML/Graphics.hpp>

using namespace Game;

ObstacleEntity::ObstacleEntity(int texture, int _id)
{
	id = _id;

	enum GameEngine::eTexture::type textEnum = static_cast<GameEngine::eTexture::type>(texture);
	m_renderComponent = static_cast<GameEngine::SpriteRenderComponent*>(AddComponent<GameEngine::SpriteRenderComponent>());
	/*m_renderComponent->SetFillColor(sf::Color::Red);*/
	m_renderComponent->SetTexture(textEnum);
	m_renderComponent->SetZLevel(2);
	m_renderComponent->SetTileIndex(0, 0);

	if (_id == 2) {
		m_colComponent = static_cast<GameEngine::CollidableComponent*>(AddComponent<GameEngine::CollidableComponent>());
	}
	else {
		m_colComponent = static_cast<GameEngine::CollidableComponent*>(AddComponent<GameEngine::CollidableComponent>());
	}
}


ObstacleEntity::~ObstacleEntity()
{

}

void ObstacleEntity::OnAddToWorld()
{
	__super::OnAddToWorld();
}


void ObstacleEntity::OnRemoveFromWorld()
{
	__super::OnRemoveFromWorld();
}

void ObstacleEntity::SetBoundingBox(sf::Vector2f size) {
	printf("!!!!!!!!");
	m_colComponent->SetBoundingBox(size);
}