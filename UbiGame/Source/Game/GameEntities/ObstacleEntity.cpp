#include "ObstacleEntity.h"

#include "GameEngine/EntitySystem/Components/CollidableComponent.h"

#include <SFML/Graphics.hpp>

using namespace Game;

ObstacleEntity::ObstacleEntity(int texture, int _id, int _curId, int zVal)
{
	id = _id;
	curId = _curId;

	enum GameEngine::eTexture::type textEnum = static_cast<GameEngine::eTexture::type>(texture);
	m_renderComponent = static_cast<GameEngine::SpriteRenderComponent*>(AddComponent<GameEngine::SpriteRenderComponent>());
	/*m_renderComponent->SetFillColor(sf::Color::Red);*/
	m_renderComponent->SetTexture(textEnum);
	m_renderComponent->SetZLevel(zVal);
	m_renderComponent->SetTileIndex(0, 0);

	AddComponent<GameEngine::CollidableComponent>();
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