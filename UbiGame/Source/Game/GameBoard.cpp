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
	m_player->SetPos(sf::Vector2f(50.f, 300.f));	
	m_player->SetSize(sf::Vector2f(114.f, 205.f));
	
	CreateBackGround();

	//Debug
	for (int a = 0; a < 3; ++a)
	{
		//SpawnNewRandomObstacles();
	}
}


GameBoard::~GameBoard()
{

}


void GameBoard::Update()
{	
	float dt = GameEngine::GameEngineMain::GetInstance()->GetTimeDelta();
	if (!m_isGameOver)
	{
		m_lastObstacleSpawnTimer -= dt;
		if (m_lastObstacleSpawnTimer <= 0.f)
		{
			//SpawnNewRandomObstacles();
			SpawnNewRandomTiledObstacles();
			SpawnNewObstacles();
		}

		UpdateObstacles(dt);
		UpdateBackGround();
		UpdatePlayerDying();
	}		
}


void GameBoard::UpdateObstacles(float dt)
{
//	static float obstacleSpeed = 100.f;
//	
//	for (std::vector<GameEngine::Entity*>::iterator it = m_obstacles.begin(); it != m_obstacles.end();)
//	{
//		GameEngine::Entity* obstacle = (*it);
//		sf::Vector2f currPos = obstacle->GetPos();
//		currPos.x -= obstacleSpeed * dt;
//		obstacle->SetPos(currPos);
//		//If we are to remove ourselves
//		if (currPos.x < -50.f)
//		{
//			GameEngine::GameEngineMain::GetInstance()->RemoveEntity(obstacle);
//			it = m_obstacles.erase(it);
//		}
//		else
//		{
//			it++;
//		}
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

void GameBoard::SpawnNewObstacles() {
	sf::Vector2f deskPos = sf::Vector2f(700.f, 600.f);
	sf::Vector2f deskSize = sf::Vector2f(630.f, 324.f);

	SpawnNewObstacle(deskPos, deskSize, 5, 2);

	sf::Vector2f doorPos = sf::Vector2f(1075.f, 200.f);
	sf::Vector2f doorSize = sf::Vector2f(248.f, 304.f);

	SpawnNewObstacle(doorPos, doorSize, 6, 2);
}

void GameBoard::SpawnNewRandomObstacles()
{
	/*static float minNextSpawnTime = 0.3f;
	static float maxNextSpawnTime = 0.7f;

	static float minObstacleXPos = 50.f;
	static float maxObstacleXPos = 450.f;
	static float minObstacleYPos = 20.f;
	static float maxObstacleYPos = 450.f;
	
	static float minObstacleHeight = 50.f;
	static float maxObstacleHeight = 170.f;
	static float minObstacleWidth = 20.f;
	static float maxObstacleWidth = 40.f;

	sf::Vector2f pos = sf::Vector2f(RandomFloatRange(minObstacleXPos, maxObstacleXPos), RandomFloatRange(minObstacleYPos, maxObstacleYPos));
	sf::Vector2f size = sf::Vector2f(RandomFloatRange(minObstacleWidth, maxObstacleWidth), RandomFloatRange(minObstacleHeight, maxObstacleHeight));

	SpawnNewObstacle(pos, size, 5);

	m_lastObstacleSpawnTimer = RandomFloatRange(minNextSpawnTime, maxNextSpawnTime);*/
}


void GameBoard::SpawnNewRandomTiledObstacles()
{
	/*static int minObstacleCount = 2;
	static int maxObstacleCount = 7;

	static float minNextSpawnTime = 0.3f;
	static float maxNextSpawnTime = 0.7f;

	static float minObstacleXPos = 350.f;
	static float maxObstacleXPos = 450.f;
	static float minObstacleYPos = 20.f;
	static float maxObstacleYPos = 450.f;

	sf::Vector2f pos = sf::Vector2f(RandomFloatRange(minObstacleXPos, maxObstacleXPos), RandomFloatRange(minObstacleYPos, maxObstacleYPos));	
	sf::Vector2f size = sf::Vector2f(32.f, 32.f);

	int obstacleCount = (int)RandomFloatRange((float)minObstacleCount, (float)maxObstacleCount);
	for (int a = 0; a < obstacleCount; ++a)
	{
		SpawnNewObstacle(pos, size, 5);
		pos.y += size.y;
	}

	m_lastObstacleSpawnTimer = RandomFloatRange(minNextSpawnTime, maxNextSpawnTime);*/
}

// Doors have half hitboxes
void GameBoard::SpawnNewDoor(const sf::Vector2f& pos, const sf::Vector2f& size, int texture) {
	ObstacleEntity* obstacle = new ObstacleEntity(texture, 2);
	obstacle->SetPos(pos);
	obstacle->SetSize(sf::Vector2f(size.x, size.y));
	obstacle->SetBoundingBox(sf::Vector2f(size.x/3, size.y/3));
	m_obstacles.push_back(obstacle);
}

void GameBoard::SpawnNewObstacle(const sf::Vector2f& pos, const sf::Vector2f& size, int texture, int _id)
{
	ObstacleEntity* obstacle = new ObstacleEntity(texture, _id);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(obstacle);
	obstacle->SetPos(pos);
	obstacle->SetSize(sf::Vector2f(size.x, size.y));

	m_obstacles.push_back(obstacle);
}


void GameBoard::CreateBackGround()
{
	GameEngine::Entity* bgEntity = new GameEngine::Entity();
	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(bgEntity->AddComponent<GameEngine::SpriteRenderComponent>());
	render->SetTexture(GameEngine::eTexture::RoomA1Bg);
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
	render->SetTexture(GameEngine::eTexture::Hallway1Bg);
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

void GameBoard::NewRoom(int _id) {
	printf("HI! %d\n", _id);
	if (_id == 2) {
		GameEngine::Entity* bgEntity = new GameEngine::Entity();
		GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(bgEntity->AddComponent<GameEngine::SpriteRenderComponent>());
		render->SetTexture(GameEngine::eTexture::Hallway1Bg);
		render->SetZLevel(z_level + 0);
		bgEntity->SetPos(sf::Vector2f(640.f, 360.f));
		bgEntity->SetSize(sf::Vector2f(1280.f, 720.f));
		GameEngine::GameEngineMain::GetInstance()->AddEntity(bgEntity);

		m_backGround = bgEntity;
	}
}

void GameBoard::PrintDialog(int _id) {
	GameEngine::Entity* dialogEntity = new GameEngine::Entity();
	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(dialogEntity->AddComponent<GameEngine::SpriteRenderComponent>());
	render->SetTexture(GameEngine::eTexture::DialogExample);
	render->SetZLevel(z_level + 4);
	dialogEntity->SetPos(sf::Vector2f(640.f, 360.f));
	dialogEntity->SetSize(sf::Vector2f(1280.f, 360.f));
	GameEngine::GameEngineMain::GetInstance()->AddEntity(dialogEntity);
	m_dialog = dialogEntity;
}

void GameBoard::HideDialog() {

	//RepaintEverything();

	//if (m_dialog != nullptr) {
	//	GameEngine::GameEngineMain::GetInstance()->RemoveEntity(m_dialog);
	//	m_dialog = nullptr;


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