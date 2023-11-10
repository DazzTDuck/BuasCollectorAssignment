#include "Game.h"
#include <iostream>
#include <random>
#include "MathFunctions.h"
using namespace sf;

//started 11/2

Game::Game() : // constructor
	_gameWindow(VideoMode(1280, 720), "Collector"),
	_tileTexture(),
	_tileHandler(),
	_generator()
{
	_tileTexture.loadFromFile("Assets/Assets/Tiles.png");
	_tileTexture.setRepeated(true);
};

void Game::Start()
{
	GameObject* player = CreateGameObject("player");

	for (auto pair : objectsList)
	{
		pair.second->Start();
	}

	//create game tiles
	CreateGameTile(Vector2f(80, 400), Grass_Begin);

	std::vector<TileTypes> tileTypes = { Grass_MiddleA, Grass_MiddleB, Grass_MiddleC };
	std::shuffle(tileTypes.begin(), tileTypes.end(), _generator);

	for (int i = 1; i < 29; i++)
	{
		TileTypes randomType = tileTypes[i % tileTypes.size()];

		CreateGameTile(Vector2f(80 + 16 * i, 400), randomType);
	}

	CreateGameTile(Vector2f(544, 400), Grass_End);
}

void Game::Run()
{
	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;

	while (_gameWindow.isOpen())
	{
		ProcessEvents();
		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > _timePerFrame)
		{
			timeSinceLastUpdate -= _timePerFrame;
			ProcessEvents();
			Update(_timePerFrame.asSeconds());

			for (auto pair : objectsList)
			{
				pair.second->Update(_timePerFrame.asSeconds());
			}
		}

		Render();
	}
}

void Game::ProcessEvents()
{
	Event event;
	while (_gameWindow.pollEvent(event))
	{
		switch (event.type)
		{
			case Event::KeyPressed:
				HandlePlayerInputs(event.key.code, true);
				break;
			case Event::KeyReleased:
				HandlePlayerInputs(event.key.code, false);
				break;
			case Event::Closed:
				_gameWindow.close();
				break;
		}
	}
}

void Game::HandlePlayerInputs(sf::Keyboard::Key key, bool isPressed)
{
	switch (key)
	{
		case Keyboard::W:
			_wKeyPressed = isPressed;
			break;
		case Keyboard::A:
			_aKeyPressed = isPressed;
			break;
		case Keyboard::S:
			_sKeyPressed = isPressed;
			break;
		case Keyboard::D:
			_dKeyPressed = isPressed;
			break;
		case Keyboard::Space:
			_spacePressed = isPressed;
			break;
	}
}

GameObject* Game::CreateGameObject(const std::string& objectName)
{
	GameObject* newObject = new GameObject();
	newObject->game = this; //reference game class

	objectsList[objectName] = newObject;

	return newObject;
}

void Game::CreateGameTile(Vector2f position, TileTypes type)
{
	activeTiles.push_back(_tileHandler.CreateNewTile(position, type));
}

void Game::Update(float deltaTime)
{
	float moveX = 0.f;

	if (_aKeyPressed)
		moveX -= 1.f; //left
	if (_dKeyPressed)
		moveX += 1.f; //right

	objectsList["player"]->SetVelocityX(moveX * _playerSpeed * deltaTime);

	//jumping
	if(_spacePressed)
	{
		float jumpVelocity = -sqrt(2 * GRAVITY * _jumpHeight);

		Vector2f force(0.f, 0.f);
		force.y = objectsList["player"]->objectMass * jumpVelocity / _jumpTime;

		objectsList["player"]->ApplyForce(force, deltaTime, true);

		_spacePressed = false;
	}

	objectsList["player"]->CheckOutOfBounds(_gameWindow);
}

void Game::Render()
{
	_gameWindow.clear();

	for (TileObject* tile : activeTiles)
	{
		tile->Draw(_gameWindow);
	}

	for (auto pair : objectsList)
	{
		pair.second->Draw(_gameWindow);
	}

	_gameWindow.display();
}

Game::~Game()
{
	for (auto pair : objectsList)
	{
		delete pair.second;
	}

	for (auto tile : activeTiles)
	{
		delete tile;
	}
}