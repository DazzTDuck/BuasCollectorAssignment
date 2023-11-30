#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "TileHandler.h"
#include "TileObject.h"
#include "GameInput.h"
#include <random>

#include "SoundManager.h"

#define GRAVITY (9.81f)

class Game
{
public:
	Game();
	void Run();
	void Start();
	GameObject* CreateGameObject(const std::string& objectName);
	void CreateGameTile(sf::Vector2f position, TileTypes tileType);

	std::map<std::string, GameObject*> objectsList;
	std::vector<TileObject*> collisionTiles;
	std::vector<TileObject*> drawTiles;

	sf::RenderWindow gameWindow;
	sf::View gameView;
	sf::Vector2f minGameViewCenter = { 640.f, 360.f};
	sf::Vector2f maxGameViewCenter = { 1920.f, 360.f};

	SoundManager* soundManager;

	~Game();

private:
	void Update(float deltaTime);
	void Render();
	void EventHandler();
	void ReadWorldFile(std::vector<std::vector<int>>& output);

	std::vector<TileTypes> _tilesToCollide = 
	{
		Grass_Begin, Grass_MiddleA, Grass_MiddleB, Grass_MiddleC,
		Grass_End, Invis_Collider, Coin, Rocks_EdgeR1, Rocks_EdgeR2,
		Rocks_EdgeL1, Rocks_EdgeL2, Rocks_UnderA, Rocks_UnderB, Rocks_UnderC
	};

	float _viewScrollSpeed = 7.f;
	sf::Time _timePerFrame =  sf::seconds(1.f / 60.f);

	std::default_random_engine _generator;
	TileHandler _tileHandler;
	sf::Music _backgroundMusic;

	sf::Texture _backgroundTexture;
	sf::Sprite _backgroundSprite;
	float _backgroundScrollOffset = 0.f;
	sf::Vector2f _backgroundScale = { 2.667f, 2.667f };
	float _scrollSpeed = 10.f;
};
