#include "Game.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include "BackgroundSprite.h"
#include "EnemyObject.h"
#include "MathFunctions.h"
#include "GameInput.h"
#include "PlayerObject.h"
using namespace sf;

//started 11/2

Game::Game() : // constructor
	gameWindow(VideoMode(1280, 720), "Collector")
{
	gameView.setSize(1280, 720);
	gameView.setCenter(640, 360); //center view on center of the screen
	gameWindow.setView(gameView);

	uiView.setSize(1280, 720);
	uiView.setCenter(640, 360);

	//make background sprite
	_backgroundTexture.loadFromFile("Assets/Background/Background.png");
	_backgroundTreeTexture.loadFromFile("Assets/Trees/Background.png");
	_treesTexture.loadFromFile("Assets/Trees/Yellow-Tree.png");
	_backgroundTexture.setRepeated(true);

	//set texture an rect so texture can scroll
	_backgroundSprite.setTexture(_backgroundTexture);
	_backgroundSprite.setTextureRect({0, 0, 1280, 720});
	_backgroundSprite.setScale(_backgroundScale);

	soundManager = new SoundManager();
	userInterface = new UserInterface();
};

void Game::Start()
{
	//initialize keyboard inputs
	Input::InitializeInputs();

	PlayerObject* player = new PlayerObject(this);
	objectsList["player"] = player;

	EnemyObject* snailEnemy = new EnemyObject(this);
	objectsList["snail"] = snailEnemy;

	//read world file
	std::vector<std::vector<int>> testVector;
	ReadWorldFile(testVector);

	int coinNumber = 1;

	//loop over results and create game tiles
	for (size_t i = 0; i < testVector.size(); i++)
	{
		for(size_t j = 0; j < testVector[i].size(); j++)
		{
			int element = testVector[i][j];

			if (element == Empty) //empty value
				continue;

			if(element == Coin)
			{
				//create coin objects
				GameObject* coin = CreateGameObject("Coin" + std::to_string(coinNumber++));
				coin->objectName = "Coin";
				coin->objectPosition = { 16.f * j, 16.f * i };
				coin->respawnLocation = coin->objectPosition;

				player->CoinAdded();

				continue;
			}

			CreateGameTile({16.f * j, 16.f * i}, static_cast<TileTypes>(element));
		}
	}

	//create all background elements
	CreateBackgroundLayers();

	//activate start function in all objects
	for (auto pair : objectsList)
	{
		pair.second->Start();
	}

	//load all sounds
	SoundManager::LoadSounds();

	//start background music
	_backgroundMusic.openFromFile("Assets/Sounds/music.wav");
	_backgroundMusic.setVolume(3.f);
	_backgroundMusic.setLoop(true);
	_backgroundMusic.play();
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

			//update user interface
			userInterface->Update(_timePerFrame.asSeconds());

			for (auto& pair : objectsList)
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

void Game::CreateBackgroundLayers()
{
	//--create background sprites--

	//Lighter trees layer (+191 & +382)
	CreateBackgroundSprite({ 0.f, 200.f }, { 2.f, 2.f }, _backgroundTreeTexture, { 352, 0, 96, 896 }, 0.9f);
	CreateBackgroundSprite({ 191.f, 200.f }, { 2.f, 2.f }, _backgroundTreeTexture, { 464, 0, 96, 896 }, 0.9f);
	CreateBackgroundSprite({ 382.f, 200.f }, { 2.f, 2.f }, _backgroundTreeTexture, { 576, 0, 127, 896 }, 0.9f);

	CreateBackgroundSprite({ 450.f, 300.f }, { 2.f, 2.f }, _backgroundTreeTexture, { 352, 0, 96, 896 }, 0.9f);
	CreateBackgroundSprite({ 641.f, 300.f }, { 2.f, 2.f }, _backgroundTreeTexture, { 464, 0, 96, 896 }, 0.9f);
	CreateBackgroundSprite({ 832.f, 300.f }, { 2.f, 2.f }, _backgroundTreeTexture, { 576, 0, 127, 896 }, 0.9f);

	//Darker trees layer (+159 & +318)
	CreateBackgroundSprite({ -175.f, 400.f }, { 1.67f, 1.67f }, _backgroundTreeTexture, { 0, 0, 96, 896 }, 0.85f);
	CreateBackgroundSprite({ -16.f, 400.f }, { 1.67f, 1.67f }, _backgroundTreeTexture, { 112, 0, 96, 896 }, 0.85f);
	CreateBackgroundSprite({ 143.0f, 400.f }, { 1.67f, 1.67f }, _backgroundTreeTexture, { 224, 0, 127, 896 }, 0.85f);

	CreateBackgroundSprite({ 375.f, 300.f }, { 1.67f, 1.67f }, _backgroundTreeTexture, { 0, 0, 96, 896 }, 0.85f);
	CreateBackgroundSprite({ 534.f, 300.f }, { 1.67f, 1.67f }, _backgroundTreeTexture, { 112, 0, 96, 896 }, 0.85f);
	CreateBackgroundSprite({ 693.0f, 300.f }, { 1.67f, 1.67f }, _backgroundTreeTexture, { 224, 0, 127, 896 }, 0.85f);

	CreateBackgroundSprite({ 800.f, 350.f }, { 1.67f, 1.67f }, _backgroundTreeTexture, { 0, 0, 96, 896 }, 0.85f);
	CreateBackgroundSprite({ 959.f, 350.f }, { 1.67f, 1.67f }, _backgroundTreeTexture, { 112, 0, 96, 896 }, 0.85f);
	CreateBackgroundSprite({ 1118.f, 350.f }, { 1.67f, 1.67f }, _backgroundTreeTexture, { 224, 0, 127, 896 }, 0.85f);

	//Biggest Yellow Tree
	CreateBackgroundSprite({ 600.f, 50.f }, { 2.f, 2.f }, _treesTexture, { 0,0,107,368 }, 0.6f);

	//Big Yellow Tree
	CreateBackgroundSprite({ 50.f, 150.f }, { 2.f, 2.f }, _treesTexture, { 0,391,110,313 }, 0.6f);

	//Medium Yellow Tree
	//CreateBackgroundSprite({ 400.f, 350.f }, { 2.f, 2.f }, _treesTexture, { 0,720,92,208 }, 0.6f);

	//Small Yellow Tree
	//CreateBackgroundSprite({ 400.f, 400.f }, { 2.f, 2.f }, _treesTexture, { 0,994,94,144 }, 0.6f);

	//Very Small Yellow Tree
	CreateBackgroundSprite({ 400.f, 260.f }, { 2.f, 2.f }, _treesTexture, { 0,1092,75,108 }, 0.f);

	//----
}


GameObject* Game::CreateGameObject(const std::string& objectName)
{
	GameObject* newObject = new GameObject(this);
	objectsList[objectName] = newObject;

	return newObject;
}

void Game::CreateGameTile(Vector2f position, TileTypes tileType)
{
	for(auto type : _tilesToCollide)
	{
		if(tileType == type)
		{
			collisionTiles.push_back(_tileHandler.CreateNewTile(position, tileType));
			return;
		}
	}

	drawTiles.push_back(_tileHandler.CreateNewTile(position, tileType));
}

void Game::CreateBackgroundSprite(sf::Vector2f position, sf::Vector2f scale, sf::Texture& texture, sf::IntRect rect, float newDepth)
{
	BackgroundSprite* newSprite = new BackgroundSprite(position, scale, texture, rect, newDepth);
	backgroundSprites.push_back(newSprite);
}

void Game::ResetGame()
{
	//respawn and reset all objects
	for (auto gameObject : objectsList)
	{
		gameObject.second->isDisabled = false;
		gameObject.second->OnRespawn();
	}

	//reset all tile position
	for (auto tile : collisionTiles)
	{
		tile->GetSprite()->setPosition(tile->startPosition);
	}

	//reset UI
	userInterface->ResetUI();
}

void Game::Update(float deltaTime)
{
	//reset sprite to 0 to make it a loop, because repeated textures are not infinite
	if (_backgroundSprite.getPosition().x < -(1280.f - 640.f * floor((gameView.getCenter().x - 640.f) / 640.f)))
	{
		_backgroundScrollOffset += 1280;
	}

	//scroll background & parallax for all background sprites
	_backgroundScrollOffset += -_scrollSpeed * deltaTime;
	_backgroundSprite.setPosition((gameView.getCenter().x - 640.f) * _backgroundDepth + _backgroundScrollOffset, 0.f);

	//other background layers
	for (auto sprite : backgroundSprites)
	{
		sprite->SetPosition({ sprite->GetStartPosition().x + (gameView.getCenter().x - 640.f) * sprite->depth, sprite->GetStartPosition().y});
	}

	float target = objectsList["player"]->objectPosition.x;

	//move game view based on player position and limit to min and max
	if (objectsList["player"]->objectPosition.x < minGameViewCenter.x)
		target = minGameViewCenter.x;
	else if(objectsList["player"]->objectPosition.x > maxGameViewCenter.x)
		target = maxGameViewCenter.x;
		
	gameView.setCenter(MathFunctions::Lerp(gameView.getCenter().x, target, _viewScrollSpeed * deltaTime), gameView.getCenter().y);
}


void Game::Render()
{
	gameWindow.clear();
	gameWindow.setView(gameView);

	//draw backgrounds
	gameWindow.draw(_backgroundSprite);

	//draw background layers
	for (BackgroundSprite* sprite : backgroundSprites)
	{
		gameWindow.draw(*sprite->GetSprite());
	}

	//draw all tiles
	for (TileObject* tile : collisionTiles)
	{
		tile->Draw(gameWindow);
	}

	for (TileObject* tile : drawTiles)
	{
		tile->Draw(gameWindow);
	}

	//draw all objects
	for (auto& pair : objectsList)
	{
		pair.second->Draw(gameWindow);
	}

	//set view to uiView and render any UI elements
	gameWindow.setView(uiView);
	userInterface->Draw(gameWindow);

	gameWindow.display();
}

Game::~Game()
{
	//delete all saved data to avoid leaks

	for (auto& pair : objectsList)
	{
		delete pair.second;
	}

	for (auto tile : collisionTiles)
	{
		delete tile;
	}

	for (auto tile : drawTiles)
	{
		delete tile;
	}

	for (auto sprite : backgroundSprites)
	{
		delete sprite;
	}


	delete userInterface;
	delete soundManager;
}