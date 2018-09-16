#pragma once
#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

namespace GameEngine
{
	//TODO - if needed, move out of Engine part to some sort of loader on the game side of things
	namespace eTexture
	{
		enum type
		{
			None = -1,
			Player = 0,
			Transparent,
			// HackRoom
			HackRoomBg,
			HackRoomDesksAndChairs,
			HackRoomDoor,
			// Elevator Hallway
			HallwayBg1,
			HallwayBg2,
			HallwayBg3,
			HallwayElevatorDoor,
			HallwaySnackTable,
			// Stairs
			StairsBg1,
			StairsBg2,
			StairsBg3,
			// Food & Sponsors
			SponsorFoodBg,
			SponsorTableBackRow,
			SponsorTableFrontRow,
			FoodTables,

			// Final
			TheaterStage,

			// Dialogue
			DialogueBox,

			DialogueDesk = 100,
			DialogueSponsor = 101,
			DialogueFood = 102,
			DialogueElevator1 = 103,
			DialogueElevator2 = 104,

			// Levels
			EnergyLevel = 200,
			TimeLevel = 201,
			HungerLevel = 202,
			ProjectCompletionLevel = 203,
			Count
		};
	}	

	inline const char* GetPath(eTexture::type texture)
	{
		switch (texture)
		{
		case eTexture::Player: return "playerModel.png";
		case eTexture::Transparent: return "trans.png";

		case eTexture::HackRoomBg: return "room-a1-bg.png";
		case eTexture::HackRoomDesksAndChairs: return "room-a1-boxes.png";
		case eTexture::HackRoomDoor: return  "room-a1-door.png";

		case eTexture::HallwayBg1: return "hallway-floor-1-bg.png";
		case eTexture::HallwayBg2: return "hallway-floor-2-bg.png";
		case eTexture::HallwayBg3: return "hallway-floor-3-bg.png";
		case eTexture::HallwayElevatorDoor: return "elevatorDoor.png";
		case eTexture::HallwaySnackTable: return "snackTable.png";

		case eTexture::StairsBg1: return "stairs-1.png";
		case eTexture::StairsBg2: return "stairs-2.png";
		case eTexture::StairsBg3: return "stairs-3.png";

		case eTexture::SponsorFoodBg: return "sponsors-1-bg.png";
		case eTexture::SponsorTableBackRow: return "sponsors-boxes-1.png";
		case eTexture::SponsorTableFrontRow: return "sponsors-boxes-2.png";
		case eTexture::FoodTables: return "cafeteria-boxes.png";

		case eTexture::TheaterStage: return "auditorium-bg.png";

		case eTexture::DialogueBox: return "dialogue.png";
		case eTexture::DialogueDesk: return "dialogueDesk.png";
		case eTexture::DialogueFood: return "dialogueFood.png";
		case eTexture::DialogueElevator1: return "dialogueElevator1.png";
		case eTexture::DialogueElevator2: return "dialogueElevator2.png";
		case eTexture::DialogueSponsor: return "dialogueSponsor.png";

		case eTexture::EnergyLevel: return "energyBar.png";
		case eTexture::TimeLevel: return "timeBar.png";
		case eTexture::HungerLevel: return "hungerBar.png";
		case eTexture::ProjectCompletionLevel: return "";

		default:       return "UnknownTexType";
		}
	}

	class TextureManager
	{
	public:
		static TextureManager* GetInstance() { if (!sm_instance) sm_instance = new TextureManager(); return sm_instance; }
		~TextureManager();

		void LoadTextures();
		void UnLoadTextures();

		sf::Texture* GetTexture(eTexture::type texture) const { return m_textures[(int)texture]; }

	private:
		TextureManager();
		static TextureManager* sm_instance;

		sf::Texture* m_textures[eTexture::Count];
	};
}

namespace TextureHelper
{
	static sf::Vector2f GetTextureTileSize(GameEngine::eTexture::type texture)
	{
		switch (texture)
		{
		case  GameEngine::eTexture::Player:  return sf::Vector2f(35.f, 63.f);

		case  GameEngine::eTexture::HackRoomBg: return sf::Vector2f(128.f, 90.f);
		case  GameEngine::eTexture::HackRoomDesksAndChairs: return sf::Vector2f(105.f, 54.f);
		case  GameEngine::eTexture::HackRoomDoor: return sf::Vector2f(31.f, 38.f);

		case  GameEngine::eTexture::HallwayBg1: return sf::Vector2f(128.f, 90.f);
		case  GameEngine::eTexture::HallwayBg2: return sf::Vector2f(128.f, 90.f);
		case  GameEngine::eTexture::HallwayBg3: return sf::Vector2f(128.f, 90.f);

		case  GameEngine::eTexture::HallwayElevatorDoor: return sf::Vector2f(30.f, 37.f);
		case  GameEngine::eTexture::HallwaySnackTable: return sf::Vector2f(23.f, 39.f);

		case  GameEngine::eTexture::StairsBg1: return sf::Vector2f(128.f, 96.f);
		case  GameEngine::eTexture::StairsBg2: return sf::Vector2f(128.f, 96.f);
		case  GameEngine::eTexture::StairsBg3: return sf::Vector2f(128.f, 96.f);
		
		case  GameEngine::eTexture::SponsorFoodBg: return sf::Vector2f(256.f, 160.f);
		case  GameEngine::eTexture::SponsorTableBackRow: return sf::Vector2f(250.f, 41.f);
		case  GameEngine::eTexture::SponsorTableFrontRow: return sf::Vector2f(202.f, 41.f);

		case  GameEngine::eTexture::FoodTables: return sf::Vector2f(214.f, 64.f);

		case  GameEngine::eTexture::TheaterStage: return sf::Vector2f(160.f, 160.f);

		case GameEngine::eTexture::DialogueBox: return sf::Vector2f(192.f, 48.f);
		case GameEngine::eTexture::DialogueDesk: return sf::Vector2f(192.f, 48.f);
		case GameEngine::eTexture::DialogueFood: return sf::Vector2f(192.f, 48.f);
		case GameEngine::eTexture::DialogueElevator1: return sf::Vector2f(192.f, 48.f);
		case GameEngine::eTexture::DialogueElevator2: return sf::Vector2f(192.f, 48.f);
		case GameEngine::eTexture::DialogueSponsor: return sf::Vector2f(192.f, 48.f);

		case GameEngine::eTexture::EnergyLevel: return sf::Vector2f(51.f, 12.f);
		case GameEngine::eTexture::HungerLevel: return sf::Vector2f(51.f, 12.f);
		case GameEngine::eTexture::TimeLevel: return sf::Vector2f(51.f, 12.f);
			// project completion level?

		case  GameEngine::eTexture::Transparent: return sf::Vector2f(100.f, 100.f);
		default:							 return sf::Vector2f(-1.f, -1.f);
		}
	}
}

