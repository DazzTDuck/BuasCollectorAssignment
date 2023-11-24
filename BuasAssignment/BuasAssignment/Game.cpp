#include "Game.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include "MathFunctions.h"
#include "GameInput.h"
#include "PlayerObject.h"
using namespace sf;

//started 11/2

Game::Game() : // constructor
	gameWindow(VideoMode(1280, 720), "Collector"),
	_generator(),
	_tileHandler(),
	_backgroundTexture()
{
	//make background sprite
	_backgroundTexture.loadFromFile("Assets/Background/Background.png");
	_backgroundTexture.setRepeated(true);

	//set texture an rect so texture can scroll
	_backgroundSprite.setTexture(_backgroundTexture);
	_backgroundSprite.setTextureRect({0, 0, 1280, 720});
	_backgroundSprite.setScale(_backgroundScale);
};

void Game::Start()
{
	//initialize keyboard inputs
	Input::InitializeInputs();

	PlayerObject* player = new PlayerObject(this);
	objectsList["player"] = player;

	GameObject* stone = CreateGameObject("Stone"); //temp stone

	for (auto pair : objectsList)
	{
		pair.second->Start();
	}

	//read world file
	std::vector<std::vector<int>> testVector;
	ReadWorldFile(testVector);

	for (size_t i = 0; i < testVector.size(); i++)
	{
		for(size_t j = 0; j < testVector[i].size(); j++)
		{
			int element = testVector[i][j];

			if(element == 0) //empty value
				continue;

			CreateGameTile({16.f * j, 16.f * i}, static_cast<TileTypes>(element));
		}
	}
}

void Game::Run()
{
	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;

	while (gameWindow.isOpen())
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
	while (gameWindow.pollEvent(event))
	{
		//handle input events to set them correctly
		Input::InputHandler(gameWindow, event);

		switch (event.type)
		{
			case Event::Closed:
				gameWindow.close();
				break;
		}
	}
}

void Game::ReadWorldFile(std::vector<std::vector<int>>& output)
{
	std::ifstream file("world.txt");
	std::string line;

	while (std::getline(file, line))
	{
		std::vector<int> row;
		std::istringstream stringStream(line);
		int num;

		while (stringStream >> num)
		{
			row.push_back(num);
		}
		output.push_back(row);
	}

	file.close();
}


GameObject* Game::CreateGameObject(const std::string& objectName)
{
	GameObject* newObject = new GameObject(this);
	objectsList[objectName] = newObject;

	return newObject;
}

void Game::CreateGameTile(Vector2f position, TileTypes type)
{
	activeTiles.push_back(_tileHandler.CreateNewTile(position, type));
}

void Game::Update(float deltaTime)
{
	//reset sprite to 0 to make it a loop, because repeated textures are not infinite
	if (_backgroundSprite.getPosition().x < -1280)
	{
		_backgroundSprite.setPosition({ _backgroundSprite.getPosition().x + 1280, 0.f });
	}

	//scroll background
	_backgroundSprite.move({ -_scrollSpeed * deltaTime, 0.f });
}

void Game::Render()
{
	gameWindow.clear();

	//draw backgrounds
	gameWindow.draw(_backgroundSprite);

	//draw all tiles
	for (TileObject* tile : activeTiles)
	{
		tile->Draw(gameWindow);
	}

	//draw all objects
	for (auto pair : objectsList)
	{
		pair.second->Draw(gameWindow);
	}

	gameWindow.display();
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