#include "GameBoard.h"

#include "GameEngine\GameEngineMain.h"
#include "GameEngine\EntitySystem\Components\CollidableComponent.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
#include "GameEngine\Util\CameraManager.h"
#include "GameEngine\Util\TextureManager.h"
#include "Game\GameEntities\PlayerEntity.h"
#include "Game\GameEntities\ObstacleEntity.h"

#include <string>

using namespace Game;

GameBoard::GameBoard()
	: m_lastObstacleSpawnTimer(0.f)
	, m_isGameOver(false)
	, m_player(nullptr)
	, m_backGround(nullptr)
	, z_level(0)
{
	m_player = new PlayerEntity(0);
	
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);
	m_player->SetPos(sf::Vector2f(200.f, 500.f));	
	m_player->SetSize(sf::Vector2f(114.f, 205.f));
	
	CreateBackGround();

	//Debug
	SpawnRoomObstacles(1);
}


GameBoard::~GameBoard()
{

}


void GameBoard::Update()
{	
/*	float dt = GameEngine::GameEngineMain::GetInstance()->GetTimeDelta();
	if (!m_isGameOver)
	{
		m_lastObstacleSpawnTimer -= dt;
		if (m_lastObstacleSpawnTimer <= 0.f)
		{
			//SpawnNewRandomObstacles();
			SpawnNewRandomTiledObstacles();
			SpawnNewObstacles();
		}*/

//		UpdateObstacles(dt);
//		UpdateBackGround();
//		UpdatePlayerDying();
//	}		
}


void GameBoard::UpdatePlayerDying()
{	
	/*bool noGameOver = GameEngine::CameraManager::IsFollowCameraEnabled();

	if (noGameOver)
		return;

	static float xToPlayerDie = 0.f;
	if (m_player->GetPos().x < xToPlayerDie)
	{
		m_isGameOver = true;
	}*/
}

void GameBoard::SpawnRoomObstacles(int id) {
	if (id == 1) { // Room A-1: Desk and door
		sf::Vector2f deskPos = sf::Vector2f(700.f, 600.f);
		sf::Vector2f deskSize = sf::Vector2f(630.f, 324.f);

		SpawnNewObstacle(deskPos, deskSize, 3, 1);

		sf::Vector2f doorPos = sf::Vector2f(1095.f, 100.f);
		sf::Vector2f doorSize = sf::Vector2f(300.f, 100.f);

		SpawnNewObstacle(doorPos, doorSize, 4, 2);

		//Top Wall boundaries
		SpawnNewObstacle(sf::Vector2f(300.f, 150.f), sf::Vector2f(1280, 100.f), 1, 1);
		//Left wall
		SpawnNewObstacle(sf::Vector2f(0.f, 360.f), sf::Vector2f(5, 720.f), 1, 1);
		//right wall
		SpawnNewObstacle(sf::Vector2f(1280.f, 360.f), sf::Vector2f(5, 720.f), 1, 1);
		//bottom wall
		SpawnNewObstacle(sf::Vector2f(640.f, 720.f), sf::Vector2f(1280.f, 5.f), 1, 1);

	}
	if (id == 2) { // Room A-2: Elevators and snacks
		//Door 3
		sf::Vector2f doorPos1 = sf::Vector2f(830.f, 120.f);
		sf::Vector2f doorSize1 = sf::Vector2f(300.f, 100.f);
		SpawnNewObstacle(doorPos1, doorSize1, 1, 3);

		//Door 4
		sf::Vector2f doorPos2 = sf::Vector2f(40.f, 500.f);
		sf::Vector2f doorSize2 = sf::Vector2f(50.f, 100.f);
		SpawnNewObstacle(doorPos2, doorSize2, 1, 4);

		// Snack Table
		sf::Vector2f snackTablePos = sf::Vector2f(1200.f, 500.f);
		sf::Vector2f snackTableSize = sf::Vector2f(184.f, 312.f);
		SpawnNewObstacle(snackTablePos, snackTableSize, 7, 1);

		//Top Wall boundaries
		SpawnNewObstacle(sf::Vector2f(640.f, 150.f), sf::Vector2f(1280.f, 5.f), 1, 1);
		//Left wall
		SpawnNewObstacle(sf::Vector2f(0.f, 360.f), sf::Vector2f(5, 720.f), 1, 1);
		//right wall
		SpawnNewObstacle(sf::Vector2f(1280.f, 360.f), sf::Vector2f(5, 720.f), 1, 1);
		//bottom wall
		SpawnNewObstacle(sf::Vector2f(640.f, 720.f), sf::Vector2f(1280.f, 5.f), 1, 1);

	}	
}

void GameBoard::SpawnNewObstacle(const sf::Vector2f& pos, const sf::Vector2f& size, int texture, int _id)
{
	ObstacleEntity* obstacle = new ObstacleEntity(texture, _id);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(obstacle);
	obstacle->SetPos(pos);
	obstacle->SetSize(sf::Vector2f(size.x, size.y));

	m_obstacles.push_back(obstacle);
}

void GameBoard::ClearObstacles() {
	for (std::vector<GameEngine::Entity*>::iterator it = m_obstacles.begin(); it != m_obstacles.end();) {
		GameEngine::Entity* obstacle = (*it);
		GameEngine::GameEngineMain::GetInstance()->RemoveEntity(obstacle);
		it = m_obstacles.erase(it);
	}
}

void GameBoard::CreateBackGround()
{
	GameEngine::Entity* bgEntity = new GameEngine::Entity();
	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(bgEntity->AddComponent<GameEngine::SpriteRenderComponent>());
	render->SetTexture(GameEngine::eTexture::HackRoomBg);
	render->SetZLevel(z_level + 0);
	bgEntity->SetPos(sf::Vector2f(640.f, 360.f));
	bgEntity->SetSize(sf::Vector2f(1280.f, 720.f));
	GameEngine::GameEngineMain::GetInstance()->AddEntity(bgEntity);

	m_backGround = bgEntity;
}

void GameBoard::UpdateBackGround()
{
	if (!m_backGround || !m_player)
		return;

	if (!GameEngine::CameraManager::IsFollowCameraEnabled())
		return;

	m_backGround->SetPos(m_player->GetPos());
}

void GameBoard::NewRoom(int _id) {
	//printf("Loading new room ID: %d\n", _id);
	GameBoard::SpawnRoomObstacles(_id);

	GameEngine::Entity* bgEntity = new GameEngine::Entity();
	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(bgEntity->AddComponent<GameEngine::SpriteRenderComponent>());

	switch (_id)
	{
	case 2: // From hacking room to elevator hallway
		render->SetTexture(GameEngine::eTexture::HallwayBg);
		m_player->SetPos(sf::Vector2f(300.f, 500.f));
		break;
	case 3: // From upper elevator hallway to lower elevator hallway
		render->SetTexture(GameEngine::eTexture::HackRoomBg);
		break;
	case 4: // From Lower
		render->SetTexture(GameEngine::eTexture::HallwayBg);
		break;
	case 5:
		render->SetTexture(GameEngine::eTexture::HallwayBg);
		break;
	case 6:
		render->SetTexture(GameEngine::eTexture::HallwayBg);
		break;
	default:
		break;
	}

	render->SetZLevel(z_level + 0);
	bgEntity->SetPos(sf::Vector2f(640.f, 360.f));
	bgEntity->SetSize(sf::Vector2f(1280.f, 720.f));
	GameEngine::GameEngineMain::GetInstance()->AddEntity(bgEntity);
	m_backGround = bgEntity;
}

void GameBoard::ShowDialogue(int _id) {
	GameEngine::Entity* dialogueEntity = new GameEngine::Entity();
	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(dialogueEntity->AddComponent<GameEngine::SpriteRenderComponent>());
	render->SetTexture(GameEngine::eTexture::DialogueBox);
	render->SetZLevel(z_level + 4);
	dialogueEntity->SetPos(sf::Vector2f(640.f, 625.f));
	dialogueEntity->SetSize(sf::Vector2f(672.f, 168.f));
	GameEngine::GameEngineMain::GetInstance()->AddEntity(dialogueEntity);
	m_dialogues.push_back(dialogueEntity);
}

void GameBoard::HideDialogue() {
	for (std::vector<GameEngine::Entity*>::iterator it = m_dialogues.begin(); it != m_dialogues.end();) {
		GameEngine::Entity* dialogue = (*it);
		GameEngine::GameEngineMain::GetInstance()->RemoveEntity(dialogue);
		it = m_dialogues.erase(it);
	}
}