#include "Game.h"
#include <iostream>
#include <random>
#include "MathFunctions.h"
#include "GameInput.h"
#include "PlayerObject.h"
using namespace sf;

//started 11/2

Game::Game() : // constructor
	_gameWindow(VideoMode(1280, 720), "Collector"),
	_generator(),
	_tileHandler()
{
};

void Game::Start()
{
	//initialize keyboard inputs
	Input::InitializeInputs();

	PlayerObject* player = new PlayerObject();
	objectsList["player"] = player;

	for (auto pair : objectsList)
	{
		pair.second->Start();
	}

	//create temp game tiles
	CreateGameTile(Vector2f(80, 400), Grass_Begin);

	std::vector<TileTypes> tileTypes = { Grass_MiddleA, Grass_MiddleB, Grass_MiddleC };
	std::shuffle(tileTypes.begin(), tileTypes.end(), _generator);

	for (int i = 1; i < 59; i++)
	{
		TileTypes randomType = tileTypes[i % tileTypes.size()];

		CreateGameTile(Vector2f(80 + 16 * i, 400), randomType);
	}

	CreateGameTile(Vector2f(1024, 400), Grass_End);

	for (int i = 1; i < 10; i++)
	{
		CreateGameTile(Vector2f(1024, 400 - 23 * i), Grass_End);
	}
}

void Game::Run()
{
	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;

	while (_gameWindow.isOpen())
	{
		EventHandler();
		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > _timePerFrame)
		{
			timeSinceLastUpdate -= _timePerFrame;
			EventHandler();
			Update(_timePerFrame.asSeconds());

			for (auto pair : objectsList)
			{
				pair.second->Update(_timePerFrame.asSeconds());
			}
		}

		Render();
	}
}

void Game::EventHandler()
{
	Event event;
	while (_gameWindow.pollEvent(event))
	{
		//handle input events to set them correctly
		Input::InputHandler(_gameWindow, event);

		switch (event.type)
		{
			case Event::Closed:
				_gameWindow.close();
				break;
		}
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