#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "TileHandler.h"
#include "TileObject.h"
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
	void ProcessEvents();
	void HandlePlayerInputs(sf::Keyboard::Key key, bool isPressed);

	sf::Vector2f _playerSize = sf::Vector2f(60.f, 100.f);
	sf::Vector2f _playerScale = sf::Vector2f(2.f, 2.f);
	sf::Time _timePerFrame =  sf::seconds(1.f / 60.f);
	float _playerSpeed = 250.f;
	float _jumpHeight = 10.f;
	float _jumpTime = 0.05f;

	bool _wKeyPressed = false;
	bool _aKeyPressed = false;
	bool _sKeyPressed = false;
	bool _dKeyPressed = false;
	bool _spacePressed = false;

	sf::RenderWindow _gameWindow;
	sf::Texture _tileTexture;
	TileHandler _tileHandler;
	std::default_random_engine _generator;

};
