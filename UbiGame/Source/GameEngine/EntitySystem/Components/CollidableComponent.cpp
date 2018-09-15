#include "CollidableComponent.h"

#include "GameEngine\EntitySystem\Entity.h"
#include "GameEngine\Util\CollisionManager.h"

using namespace GameEngine;

CollidableComponent::CollidableComponent()
	: m_AABBBox()
	, m_useDefaultBox(true)
{

}

// Constructor overloaded to account for exit object
//CollidableComponent::CollidableComponent(bool isExit)
//	: m_AABBBox()
//	, m_useDefaultBox(true)
//{
//
//}


CollidableComponent::~CollidableComponent()
{

}


void CollidableComponent::OnAddToWorld()
{
	__super::OnAddToWorld();
	CollisionManager::GetInstance()->RegisterCollidable(this);

	if (m_useDefaultBox)
		SetupDefaultBoundingBox();
}


void CollidableComponent::OnRemoveFromWorld()
{
	__super::OnRemoveFromWorld();

	CollisionManager::GetInstance()->UnRegisterCollidable(this);
}


void CollidableComponent::SetupDefaultBoundingBox()
{
	//Static AABB for the time being		
	SetBoundingBox(GetEntity()->GetSize());
}


void CollidableComponent::SetBoundingBox(sf::Vector2f size)
{
	m_AABBBox.width = size.x;
	m_AABBBox.height = size.y;

	m_AABBBox.left = -m_AABBBox.width / 2.f;
	m_AABBBox.top = -m_AABBBox.height / 2.f;

	m_useDefaultBox = false;
}

const AABBRect CollidableComponent::GetWorldAABB() const
{ 
	AABBRect box = m_AABBBox;
	
	box.left += GetEntity()->GetPos().x;
	box.top  += GetEntity()->GetPos().y;	

	return box;
}