#include "CollidablePhysicsComponent.h"

#include "GameEngine/Util/CollisionManager.h"
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine\GameEngineMain.h"

#include <vector>
#include <iostream>

using namespace GameEngine;

CollidablePhysicsComponent::CollidablePhysicsComponent()
{

}


CollidablePhysicsComponent::~CollidablePhysicsComponent()
{

}


void CollidablePhysicsComponent::OnAddToWorld()
{
	__super::OnAddToWorld();
}


void CollidablePhysicsComponent::OnRemoveFromWorld()
{
	__super::OnAddToWorld();
}


void CollidablePhysicsComponent::Update()
{
	//For the time being just a simple intersection check that moves the entity out of all potential intersect boxes
	std::vector<CollidableComponent*>& collidables = CollisionManager::GetInstance()->GetCollidables();

	for (int a = 0; a < collidables.size(); ++a)
	{
		CollidableComponent* colComponent = collidables[a];
		if (colComponent == this)
			// Detect if this is a room exit
			// if (this->GetEntity()->GetID())
			continue;

		AABBRect intersection;
		AABBRect myBox = GetWorldAABB();
		AABBRect collideBox = colComponent->GetWorldAABB();
		if (myBox.intersects(collideBox, intersection))
		{
			int id = colComponent->GetEntity()->id;

			printf("collision %d\n", id);

			switch(id) {
			case 1:
				// Hack at desk
			case 2:
				// Exit
				GameEngineMain::GetInstance()->m_gameBoard->NewRoom(id);
			}

			sf::Vector2f pos = GetEntity()->GetPos();
			if (intersection.width < intersection.height)
			{
				if (myBox.left < collideBox.left)
					pos.x -= intersection.width;
				else
					pos.x += intersection.width;
			}
			else
			{
				if (myBox.top < collideBox.top)
					pos.y -= intersection.height;
				else
					pos.y += intersection.height;
			}


			GetEntity()->SetPos(pos);
		}
	}
}