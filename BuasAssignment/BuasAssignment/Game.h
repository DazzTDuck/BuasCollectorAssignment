#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "TileHandler.h"
#include "TileObject.h"
#include "GameInput.h"

#include "BackgroundSprite.h"
#include "SoundManager.h"
#include "UserInterface.h"

#define GRAVITY (9.81f)

class Game
{
public:
	Game();
	void Run();
	void Start();
	GameObject* CreateGameObject(const std::string& objectName);
	void CreateGameTile(sf::Vector2f position, TileTypes tileType);
	void CreateBackgroundSprite(sf::Vector2f position, sf::Vector2f scale, sf::Texture& texture, sf::IntRect rect, float newDepth, bool foreground = false);
	void ResetGame();

	std::map<std::string, GameObject*> objectsList;
	std::vector<TileObject*> collisionTiles;
	std::vector<TileObject*> drawTiles;
	std::vector<TileObject*> flowerTiles;
	std::vector<BackgroundSprite*> backgroundSprites;
	std::vector<BackgroundSprite*> foregroundSprites;

	sf::RenderWindow gameWindow;
	sf::View gameView;
	sf::View uiView;

	sf::Vector2f minGameViewCenter = { 330.f, 400.f };
	sf::Vector2f maxGameViewCenter = {2880.f, 400.f};

	SoundManager* soundManager;
	UserInterface* userInterface;

	~Game();

private:
	void Update(float deltaTime);
	void Render();
	void EventHandler();
	void ReadWorldFile(std::vector<std::vector<int>>& output);
	void CreateBackgroundLayers();

	std::vector<TileTypes> _tilesToCollide = 
	{
		Grass_Begin, Grass_MiddleA, Grass_MiddleB, Grass_MiddleC,
		Grass_End, Invis_Collider, Coin, Rocks_EdgeR1, Rocks_EdgeR2,
		Rocks_EdgeL1, Rocks_EdgeL2, Rocks_UnderA, Rocks_UnderB, Rocks_UnderC,
		Bridge_Begin, Bridge_MiddleA, Bridge_MiddleB, Bridge_MiddleC, Bridge_End,
		RockGrass_Begin, RockGrass_End, Bridge_ExtraA, Bridge_ExtraB, Bridge_ExtraC, Chest,
		Rock_Begin, Rock_MiddleA, Rock_MiddleB, Rock_MiddleC, Rock_End
	};

	std::vector<TileTypes> _flowerTiles =
	{
		Mushroom_A, Mushroom_B, Flower_A, Flower_B, Flower_C, GrassPiece
	};

	float _viewScrollSpeed = 7.f;
	sf::Time _timePerFrame =  sf::seconds(1.f / 60.f);

	TileHandler _tileHandler;
	sf::Music _backgroundMusic;

	sf::Texture _backgroundTexture;
	sf::Texture _backgroundTreeTexture;
	sf::Texture _treesTexture;
	sf::Sprite _backgroundSprite;
	float _backgroundScrollOffset = 0.f;
	float _backgroundDepth = 0.95f;
	sf::Vector2f _backgroundScale = { 1.335f, 1.335f };
	float _scrollSpeed = 10.f;
	int enemyCount = 0;
};
