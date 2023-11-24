#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "TileHandler.h"
#include "TileObject.h"
#include "GameInput.h"
#include <random>

#define GRAVITY (9.81f)

class Game
{
public:
	Game();
	void Run();
	void Start();
	GameObject* CreateGameObject(const std::string& objectName);
	void CreateGameTile(sf::Vector2f position, TileTypes type);

	std::map<std::string, GameObject*> objectsList;
	std::vector<TileObject*> activeTiles;

	sf::RenderWindow gameWindow;

	~Game();

private:
	void Update(float deltaTime);
	void Render();
	void EventHandler();
	void ReadWorldFile(std::vector<std::vector<int>>& output);

	sf::Time _timePerFrame =  sf::seconds(1.f / 60.f);

	std::default_random_engine _generator;
	TileHandler _tileHandler;

	sf::Texture _backgroundTexture;
	sf::Sprite _backgroundSprite;
	sf::Vector2f _backgroundScale = { 2.667f, 2.667f };
	float _scrollSpeed = 10.f;
};
