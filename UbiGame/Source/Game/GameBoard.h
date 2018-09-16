#pragma once
#include "GameEngine\EntitySystem\Entity.h"

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <string>

using namespace std;

namespace Game
{
	//Used for storing and controling all game related entities
	class PlayerEntity;	

	class GameBoard
	{
	public:
		GameBoard();
		virtual ~GameBoard();

		//Temp - for nice architecture this should be within some sort of IUpdatable interface that GameEngine handles (so that not only entities can be updated)
		void Update();
		void UpdatePlayerDying();
		void SpawnNewDoor(const sf::Vector2f& pos, const sf::Vector2f& size, int texture);
		void SpawnRoomObstacles(int id);
		void SpawnNewObstacle(const sf::Vector2f& pos, const sf::Vector2f& size, int texture, int _id, int _curId, int zVal=2);
		void ClearObstacles();

		bool IsGameOver() const { return m_isGameOver; }	

		void NewRoom(int _id, int _prevId);
		void PrintDialog(int _id);
		void HideDialog(GameEngine::Entity* diag);

	protected:
		//Placeholder temp - should go to helpers or smth.
		float RandomFloatRange(float a, float b)
		{
			return ((b - a) * ((float)rand() / RAND_MAX)) + a;
		}

		void CreateBackGround();
		void UpdateBackGround();
		void RepaintEverything();

		PlayerEntity* m_player;
		GameEngine::Entity* m_backGround;
		GameEngine::Entity* m_dialog;

		int z_level;

		std::vector<GameEngine::Entity*> m_obstacles;
		float m_lastObstacleSpawnTimer;
		bool  m_isGameOver;
	};
}

