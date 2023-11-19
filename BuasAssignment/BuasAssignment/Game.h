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

	~Game();

private:
	void Update(float deltaTime);
	void Render();
	void EventHandler();

	sf::Vector2f _playerSize = sf::Vector2f(60.f, 100.f);
	sf::Vector2f _playerScale = sf::Vector2f(2.f, 2.f);
	sf::Time _timePerFrame =  sf::seconds(1.f / 60.f);
	float _playerSpeed = 310.f;
	float _jumpHeight = 10.f;
	float _jumpTime = 0.05f;

	sf::RenderWindow _gameWindow;
	std::default_random_engine _generator;
	TileHandler _tileHandler;
};
