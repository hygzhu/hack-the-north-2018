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
	, m_dialog(nullptr)
	, z_level(0)
{
	m_player = new PlayerEntity(0);
	
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);
	m_player->SetPos(sf::Vector2f(200.f, 500.f));	
	m_player->SetSize(sf::Vector2f(114.f, 205.f));
	
	CreateBackGround();

	//Initial room
	SpawnRoomObstacles(3);
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

	if (id == 3) { // Room A-1: Desk and door
		sf::Vector2f deskPos = sf::Vector2f(700.f, 600.f);
		sf::Vector2f deskSize = sf::Vector2f(630.f, 324.f);

		SpawnNewObstacle(deskPos, deskSize, 3, 1, id);

		sf::Vector2f doorPos = sf::Vector2f(1095.f, 100.f);
		sf::Vector2f doorSize = sf::Vector2f(300.f, 100.f);

		SpawnNewObstacle(doorPos, doorSize, 1, 2, id);

		//Top Wall boundaries
		SpawnNewObstacle(sf::Vector2f(300.f, 150.f), sf::Vector2f(1280, 100.f), 1, 1, id);
		//Left wall
		SpawnNewObstacle(sf::Vector2f(0.f, 360.f), sf::Vector2f(10, 720.f), 1, 1, id);
		//right wall
		SpawnNewObstacle(sf::Vector2f(1280.f, 360.f), sf::Vector2f(10, 720.f), 1, 1, id);
		//bottom wall
		SpawnNewObstacle(sf::Vector2f(640.f, 720.f), sf::Vector2f(1280.f, 5.f), 1, 1, id);

	}
	if (id == 2) { // Room A-2: Elevators and snacks
		// (GO TO BOTTOM ELEVATOR 4)
		sf::Vector2f doorPos1 = sf::Vector2f(830.f, 120.f);
		sf::Vector2f doorSize1 = sf::Vector2f(300.f, 100.f);
		SpawnNewObstacle(doorPos1, doorSize1, 1, 4, id);

		// Snack Table
		sf::Vector2f snackTablePos = sf::Vector2f(1200.f, 500.f);
		sf::Vector2f snackTableSize = sf::Vector2f(184.f, 312.f);
		SpawnNewObstacle(snackTablePos, snackTableSize, 9, 1, id);

		//Top Wall boundaries
		SpawnNewObstacle(sf::Vector2f(640.f, 150.f), sf::Vector2f(1280.f, 10.f), 1, 1, id);
		//Left wall (GO TO ROOM 3)
		SpawnNewObstacle(sf::Vector2f(0.f, 360.f), sf::Vector2f(10, 720.f), 1, 3, id);
		//right wall
		SpawnNewObstacle(sf::Vector2f(1280.f, 360.f), sf::Vector2f(10, 720.f), 1, 1, id);
		//bottom wall (GO TO ROOM 5)
		SpawnNewObstacle(sf::Vector2f(640.f, 720.f), sf::Vector2f(1280.f, 10.f), 1, 5, id);

	}	
	if (id == 4) { //ELAVATOR AND SNACK 2: ELECTRIC BOOLGJOISD

		// (GO TO BOTTOM ELEVATOR 2)
		sf::Vector2f doorPos1 = sf::Vector2f(830.f, 120.f);
		sf::Vector2f doorSize1 = sf::Vector2f(300.f, 100.f);
		SpawnNewObstacle(doorPos1, doorSize1, 1, 2, id);

		// Snack Table
		sf::Vector2f snackTablePos = sf::Vector2f(1200.f, 500.f);
		sf::Vector2f snackTableSize = sf::Vector2f(184.f, 312.f);
		SpawnNewObstacle(snackTablePos, snackTableSize, 9, 1, id);

		//Top Wall boundaries
		SpawnNewObstacle(sf::Vector2f(640.f, 150.f), sf::Vector2f(1280.f, 10.f), 1, 1, id);
		//Left wall 
		SpawnNewObstacle(sf::Vector2f(0.f, 360.f), sf::Vector2f(10, 720.f), 1, 1, id);
		//right wall 
		SpawnNewObstacle(sf::Vector2f(1280.f, 360.f), sf::Vector2f(10, 720.f), 1, 1, id);
		//bottom wall (Door 6)
		SpawnNewObstacle(sf::Vector2f(640.f, 720.f), sf::Vector2f(1280.f, 10.f), 1, 6, id);
	}
	if (id == 5) {

		//left Stair
		SpawnNewObstacle(sf::Vector2f(130.f, 540.f), sf::Vector2f(20, 100.f), 1, 1, id);
		//Right stair (GOTO 6 STAIR)
		SpawnNewObstacle(sf::Vector2f(490.f, 540.f), sf::Vector2f(20, 100.f), 1, 6, id);

		//Top Wall boundaries
		SpawnNewObstacle(sf::Vector2f(640.f, 110.f), sf::Vector2f(1280.f, 10.f), 1, 1, id);
		//Left wall 
		SpawnNewObstacle(sf::Vector2f(130.f, 360.f), sf::Vector2f(10, 720.f), 1, 1, id);
		//right wall 
		SpawnNewObstacle(sf::Vector2f(490.f, 360.f), sf::Vector2f(10, 720.f), 1, 1, id);
		//bottom wall (Door 2)
		SpawnNewObstacle(sf::Vector2f(640.f, 720.f), sf::Vector2f(1280.f, 10.f), 1, 2, id);
	}
	if (id == 6) {
		//left Stair (GOTO 5 STAIR)
		SpawnNewObstacle(sf::Vector2f(130.f, 540.f), sf::Vector2f(20, 100.f), 1, 5, id);
		//Right stair (GOTO 8 ROOM)
		SpawnNewObstacle(sf::Vector2f(490.f, 540.f), sf::Vector2f(20, 100.f), 1, 8, id);

		//Top Wall boundaries (GO TO SEVEN WHICH IS SPONSORS)
		SpawnNewObstacle(sf::Vector2f(640.f, 110.f), sf::Vector2f(1280.f, 10.f), 1, 7, id);
		//Left wall 
		SpawnNewObstacle(sf::Vector2f(130.f, 360.f), sf::Vector2f(10, 720.f), 1, 1, id);
		//right wall 
		SpawnNewObstacle(sf::Vector2f(490.f, 360.f), sf::Vector2f(10, 720.f), 1, 1, id);
		//bottom wall (Door 4)
		SpawnNewObstacle(sf::Vector2f(640.f, 720.f), sf::Vector2f(1280.f, 10.f), 1, 4, id);
	}

	if (id == 7) {
		//Top Wall boundaries
		SpawnNewObstacle(sf::Vector2f(640.f, 50.f), sf::Vector2f(1280, 50.f), 1, 1, id);
		//Left wall
		SpawnNewObstacle(sf::Vector2f(0.f, 360.f), sf::Vector2f(10, 720.f), 1, 1, id);
		//right wall (RETURN TO STAIIR 6)
		SpawnNewObstacle(sf::Vector2f(1280.f, 360.f), sf::Vector2f(10, 720.f), 1, 6, id);
		//bottom wall
		SpawnNewObstacle(sf::Vector2f(640.f, 720.f), sf::Vector2f(1280.f, 10.f), 1, 1, id);
	}

	if (id == 8) {
		//left Stair (GOTO 6 STAIR)
		SpawnNewObstacle(sf::Vector2f(130.f, 540.f), sf::Vector2f(20, 100.f), 1, 6, id);
		//Right stair (GOTO 9 ROOM)
		SpawnNewObstacle(sf::Vector2f(490.f, 540.f), sf::Vector2f(20, 100.f), 1, 9, id);

		//Top Wall boundaries 
		SpawnNewObstacle(sf::Vector2f(640.f, 110.f), sf::Vector2f(1280.f, 10.f), 1, 1, id);
		//Left wall 
		SpawnNewObstacle(sf::Vector2f(130.f, 360.f), sf::Vector2f(10, 720.f), 1, 1, id);
		//right wall 
		SpawnNewObstacle(sf::Vector2f(490.f, 360.f), sf::Vector2f(10, 720.f), 1, 1, id);
		//bottom wall 
		SpawnNewObstacle(sf::Vector2f(640.f, 720.f), sf::Vector2f(1280.f, 10.f), 1, 1, id);
	}

	if (id == 9) {
		//Top Wall boundaries
		SpawnNewObstacle(sf::Vector2f(640.f, 50.f), sf::Vector2f(1280, 50.f), 1, 1, id);
		//Left wall
		SpawnNewObstacle(sf::Vector2f(0.f, 360.f), sf::Vector2f(10, 720.f), 1, 8, id);
		//right wall
		SpawnNewObstacle(sf::Vector2f(1280.f, 360.f), sf::Vector2f(10, 720.f), 1, 1, id);
		//bottom wall
		SpawnNewObstacle(sf::Vector2f(640.f, 720.f), sf::Vector2f(1280.f, 10.f), 1, 1, id);
	}
}

void GameBoard::SpawnNewObstacle(const sf::Vector2f& pos, const sf::Vector2f& size, int texture, int _id, int _curId)
{
	ObstacleEntity* obstacle = new ObstacleEntity(texture, _id, _curId);
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

void GameBoard::RepaintEverything()
{
	z_level += 5;
	
	//GameEngine::GameEngineMain::GetInstance()->RemoveEntity(m_backGround);

	GameEngine::Entity* bgEntity = new GameEngine::Entity();
	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(bgEntity->AddComponent<GameEngine::SpriteRenderComponent>());
	render->SetTexture(GameEngine::eTexture::HallwayBg1);
	render->SetZLevel(z_level + 0);
	bgEntity->SetPos(sf::Vector2f(640.f, 360.f));
	bgEntity->SetSize(sf::Vector2f(1280.f, 720.f));
	GameEngine::GameEngineMain::GetInstance()->AddEntity(bgEntity);
	m_backGround = bgEntity;

	//m_player->RerenderPlayer(z_level);
	sf::Vector2f oldPlayerPos = m_player->GetPos();
	//GameEngine::GameEngineMain::GetInstance()->RemoveEntity(m_player);

	m_player = new PlayerEntity(z_level);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);
	m_player->SetPos(oldPlayerPos);
	m_player->SetSize(sf::Vector2f(114.f, 205.f));
}

void GameBoard::NewRoom(int _id, int _prevId) {
	printf("Loading new room ID: %d, Prev ID: %d\n", _id, _prevId);
	GameBoard::SpawnRoomObstacles(_id);

	GameEngine::Entity* bgEntity = new GameEngine::Entity();
	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(bgEntity->AddComponent<GameEngine::SpriteRenderComponent>());

	switch (_id)
	{
	case 1:
		printf("SHOULD NOT BE HERE!");
		break;
	case 2: // Upper Elevator
		render->SetTexture(GameEngine::eTexture::HallwayBg3);
		printf("Prev ID: %d", _prevId);
		switch (_prevId) // Determine where the player is coming from and spawn the player from that direction
		{
		case 3:
			m_player->SetPos(sf::Vector2f(150.f, 450.f));
			break;
		case 4:
			m_player->SetPos(sf::Vector2f(825.f, 400.f));
			break;
		case 5:
			m_player->SetPos(sf::Vector2f(640.f, 550.f));
			break;
		default:
			break;
		}
		break;
	case 3: // From upper elevator hallway to lower elevator hallway
		render->SetTexture(GameEngine::eTexture::HackRoomBg);
		m_player->SetPos(sf::Vector2f(1100.f, 300.f));
		break;
	case 4: // From elevator hallway to hacker room
		render->SetTexture(GameEngine::eTexture::HallwayBg2);
		switch (_prevId) // Determine where the player is coming from and spawn the player from that direction
		{
		case 2:
			m_player->SetPos(sf::Vector2f(825.f, 400.f));
			break;
		case 6:
			m_player->SetPos(sf::Vector2f(640.f, 550.f));
			break;
		default:
			break;
		}
		break;
	case 5:
		render->SetTexture(GameEngine::eTexture::StairsBg3);
		switch (_prevId) // Determine where the player is coming from and spawn the player from that direction
		{
		case 2:
			m_player->SetPos(sf::Vector2f(300.f, 550.f));
			break;
		case 6:
			m_player->SetPos(sf::Vector2f(350.f, 500.f));
			break;
		default:
			break;
		}
		break;
	case 6:
		render->SetTexture(GameEngine::eTexture::StairsBg2);
		switch (_prevId) // Determine where the player is coming from and spawn the player from that direction
		{
		case 4:
			m_player->SetPos(sf::Vector2f(300.f, 550.f));
			break;
		case 5:
			m_player->SetPos(sf::Vector2f(250.f, 500.f));
			break;
		case 7:
			m_player->SetPos(sf::Vector2f(300.f, 300.f));
			break;
		default:
			break;
		}
		break;
	case 7:
		render->SetTexture(GameEngine::eTexture::SponsorFoodBg);
		m_player->SetPos(sf::Vector2f(1100.f, 300.f));
		break;
	case 8:
		render->SetTexture(GameEngine::eTexture::StairsBg1);
		switch (_prevId) // Determine where the player is coming from and spawn the player from that direction
		{
		case 6:
			m_player->SetPos(sf::Vector2f(250.f, 500.f));
			break;
		case 9:
			m_player->SetPos(sf::Vector2f(300.f, 500.f));
			break;
		default:
			break;
		}
		break;
	case 9:
		render->SetTexture(GameEngine::eTexture::SponsorFoodBg);
		switch (_prevId) // Determine where the player is coming from and spawn the player from that direction
		{
		case 8:
			m_player->SetPos(sf::Vector2f(150.f, 320.f));
			break;
		default:
			break;
		}
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
// TODO: CHRISTINA
/*
void GameBoard::PrintDialog(int _id) {
	GameEngine::Entity* dialogEntity = new GameEngine::Entity();
	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(dialogEntity->AddComponent<GameEngine::SpriteRenderComponent>());
	render->SetTexture(GameEngine::eTexture::DialogExample);
	render->SetZLevel(z_level + 4);
	dialogEntity->SetPos(sf::Vector2f(640.f, 360.f));
	dialogEntity->SetSize(sf::Vector2f(1280.f, 360.f));
	GameEngine::GameEngineMain::GetInstance()->AddEntity(dialogEntity);
	m_dialog = dialogEntity;
}*/

void GameBoard::HideDialog(GameEngine::Entity* diag) {

	//RepaintEverything();
/*
	sf::Transform d;
	d.scale(sf::Vector2f(0.f, 0.f));*/

	//diag = static_cast<GameEngine::Entity>(d);

	//	//create invis diag to replace
	//	GameEngine::Entity* dialogEntity = new GameEngine::Entity();
	//	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(dialogEntity->AddComponent<GameEngine::SpriteRenderComponent>());
	//	render->SetTexture(GameEngine::eTexture::DialogExample);
	//	render->SetZLevel(-1);
	//	dialogEntity->SetPos(sf::Vector2f(640.f, 360.f));
	//	dialogEntity->SetSize(sf::Vector2f(128.f, 36.f));
	//	GameEngine::GameEngineMain::GetInstance()->AddEntity(dialogEntity);
	//	m_dialog = dialogEntity;
	//}
}