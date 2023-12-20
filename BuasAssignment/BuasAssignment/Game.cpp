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
	gameView.setCenter(330, 400); //center view on center of the screen
	gameView.zoom(0.5f);
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

			switch (static_cast<TileTypes>(element))
			{
				case Empty:
					//nothing
					break;
				case Player:
					//set player position
					player->objectPosition = { 16.f * j, 16.f * i };
					player->respawnLocation = player->objectPosition;
					break;
				case Coin:
					//create coin objects
					GameObject* coin;
					coin = CreateGameObject("Coin" + std::to_string(coinNumber++));
					coin->GetSprite().setTextureRect(TileHandler::tileDefinitions.at(Coin));
					coin->objectName = "Coin";
					coin->objectType = COIN;
					coin->objectPosition = { 16.f * j, 16.f * i };
					coin->respawnLocation = coin->objectPosition;
					//register coin 
					player->CoinAdded();
					break;
				case Chest:
					//create chest for the end state
					GameObject* chest;
					chest = CreateGameObject("Chest" + std::to_string(coinNumber++));
					chest->GetSprite().setTextureRect(TileHandler::tileDefinitions.at(Chest));
					chest->objectName = "Chest";
					chest->objectType = CHEST;
					chest->objectPosition = { 16.f * j, 16.f * i };
					chest->respawnLocation = chest->objectPosition;
					break;
				case SnailEnemy:
					//create snail enemy
					EnemyObject* snailEnemy;
					snailEnemy = new EnemyObject(this);
					snailEnemy->objectName = "Snail";
					snailEnemy->objectPosition = { 16.f * j, 16.f * i };
					snailEnemy->respawnLocation = snailEnemy->objectPosition;
					objectsList["snail"] = snailEnemy;
					break;
				case BoarEnemy:
					break;
				default: //create tile
					CreateGameTile({ 16.f * j, 16.f * i }, static_cast<TileTypes>(element));
					break;
			}
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

	//Lighter trees layer (+95 & +190.f)
	CreateBackgroundSprite({ -25.f * 1.1f, 295.f }, { 1.1f, 1.1f }, _backgroundTreeTexture, { 352, 0, 96, 896 }, 0.9f);
	CreateBackgroundSprite({ 70.f * 1.1f, 295.f }, { 1.1f, 1.1f }, _backgroundTreeTexture, { 464, 0, 96, 896 }, 0.9f);
	CreateBackgroundSprite({ 165.f * 1.1f, 295.f }, { 1.1f, 1.1f }, _backgroundTreeTexture, { 576, 0, 127, 896 }, 0.9f);

	CreateBackgroundSprite({ 325.f * 1.f, 275.f }, { 1.f, 1.f }, _backgroundTreeTexture, { 352, 0, 96, 896 }, 0.9f);
	CreateBackgroundSprite({ 420.f * 1.f, 275.f }, { 1.f, 1.f }, _backgroundTreeTexture, { 464, 0, 96, 896 }, 0.9f);
	CreateBackgroundSprite({ 515.f * 1.f, 275.f }, { 1.f, 1.f }, _backgroundTreeTexture, { 576, 0, 127, 896 }, 0.9f);

	CreateBackgroundSprite({ 500.f * 1.2f, 350.f }, { 1.2f, 1.2f }, _backgroundTreeTexture, { 352, 0, 96, 896 }, 0.9f);
	CreateBackgroundSprite({ 595.f * 1.2f, 350.f }, { 1.2f, 1.2f }, _backgroundTreeTexture, { 464, 0, 96, 896 }, 0.9f);
	CreateBackgroundSprite({ 690.f * 1.2f, 350.f }, { 1.2f, 1.2f }, _backgroundTreeTexture, { 576, 0, 127, 896 }, 0.9f);

	////Darker trees layer (+95 & +190) 
	CreateBackgroundSprite({ -95.f * 1.f, 350.f }, { 1.f, 1.f }, _backgroundTreeTexture, { 0, 0, 96, 896 }, 0.85f);
	CreateBackgroundSprite({ 0.f * 1.f, 350.f }, { 1.f, 1.f }, _backgroundTreeTexture, { 112, 0, 96, 896 }, 0.85f);
	CreateBackgroundSprite({ 95.f * 1.f, 350.f }, { 1.f, 1.f }, _backgroundTreeTexture, { 224, 0, 127, 896 }, 0.85f);

	CreateBackgroundSprite({ 175.f * 1.2f, 375.f }, { 1.2f, 1.2f }, _backgroundTreeTexture, { 0, 0, 96, 896 }, 0.85f);
	CreateBackgroundSprite({ 270.f * 1.2f, 375.f }, { 1.2f, 1.2f }, _backgroundTreeTexture, { 112, 0, 96, 896 }, 0.85f);
	CreateBackgroundSprite({ 365.f * 1.2f, 375.f }, { 1.2f, 1.2f }, _backgroundTreeTexture, { 224, 0, 127, 896 }, 0.85f);

	CreateBackgroundSprite({ 475.f * 1.3f, 400.f }, { 1.3f, 1.3f }, _backgroundTreeTexture, { 0, 0, 96, 896 }, 0.85f);
	CreateBackgroundSprite({ 570.f * 1.3f, 400.f }, { 1.3f, 1.3f }, _backgroundTreeTexture, { 112, 0, 96, 896 }, 0.85f);
	CreateBackgroundSprite({ 665.f * 1.3f, 400.f }, { 1.3f, 1.3f }, _backgroundTreeTexture, { 224, 0, 127, 896 }, 0.85f);

	//Biggest Yellow Tree
	CreateBackgroundSprite({ 500.f, 240.f }, { 1.f, 1.f }, _treesTexture, { 0,0,107,368 }, 0.6f);
	CreateBackgroundSprite({ 925.f, 240.f }, { 1.f, 1.f }, _treesTexture, { 0,0,107,368 }, 0.6f);
	CreateBackgroundSprite({ 1200.f, 300.f }, { 1.f, 1.f }, _treesTexture, { 0,0,107,368 }, 0.6f);
	CreateBackgroundSprite({ 3550.f, 325.f }, { 1.f, 1.f }, _treesTexture, { 0,0,107,368 }, -0.6f, true);

	//Big Yellow Tree
	CreateBackgroundSprite({ 125.f, 280.f }, { 1.f, 1.f }, _treesTexture, { 0,391,110,313 }, 0.6f);
	CreateBackgroundSprite({ 1050.f, 340.f }, { 1.f, 1.f }, _treesTexture, { 0,391,110,313 }, 0.6f);
	CreateBackgroundSprite({ 1600.f, 280.f }, { 1.f, 1.f }, _treesTexture, { 0,391,110,313 }, 0.6f);
	CreateBackgroundSprite({ 1750.f, 300.f }, { 1.f, 1.f }, _treesTexture, { 0,391,110,313 }, -0.6f, true);

	//Medium Yellow Tree
	CreateBackgroundSprite({ 800.f, 400.f }, { 1.f, 1.f }, _treesTexture, { 0,720,92,208 }, 0.6f);
	CreateBackgroundSprite({ 1400.f, 385.f }, { 1.f, 1.f }, _treesTexture, { 0,720,92,208 }, 0.6f);

	//Small Yellow Tree
	CreateBackgroundSprite({ 1850.f, 225.f }, { 1.f, 1.f }, _treesTexture, { 0,944,94,144 }, 0.f);
	
	//Very Small Yellow Tree
	CreateBackgroundSprite({ 400.f, 385.f }, {1.f, 1.f }, _treesTexture, { 0,1092,75,108 }, 0.f);

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

	for (auto type : _flowerTiles)
	{
		if (tileType == type)
		{
			flowerTiles.push_back(_tileHandler.CreateNewTile(position, tileType));
			return;
		}
	}

	drawTiles.push_back(_tileHandler.CreateNewTile(position, tileType));
}

void Game::CreateBackgroundSprite(sf::Vector2f position, sf::Vector2f scale, sf::Texture& texture, sf::IntRect rect, float newDepth, bool foreground)
{
	BackgroundSprite* newSprite = new BackgroundSprite(position, scale, texture, rect, newDepth);

	foreground ? foregroundSprites.push_back(newSprite) : backgroundSprites.push_back(newSprite);
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
	if (_backgroundSprite.getPosition().x < -(640.f - minGameViewCenter.x * floor((gameView.getCenter().x - minGameViewCenter.x) / minGameViewCenter.x)))
	{
		_backgroundScrollOffset += 640.f;
	}

	//scroll background & parallax for all background sprites
	_backgroundScrollOffset += -_scrollSpeed * deltaTime;
	_backgroundSprite.setPosition((gameView.getCenter().x - minGameViewCenter.x) * _backgroundDepth + _backgroundScrollOffset, 220.f);

	//other background layers
	for (auto sprite : backgroundSprites)
	{
		sprite->SetPosition({ sprite->GetStartPosition().x + (gameView.getCenter().x - minGameViewCenter.x) * sprite->depth, sprite->GetStartPosition().y});
	}

	for (auto sprite : foregroundSprites)
	{
		sprite->SetPosition({ sprite->GetStartPosition().x + (gameView.getCenter().x - minGameViewCenter.x) * sprite->depth, sprite->GetStartPosition().y });
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

	//draw flowers
	for (TileObject* tile : flowerTiles)
	{
		tile->Draw(gameWindow);
	}

	//draw all objects
	for (auto& pair : objectsList)
	{
		pair.second->Draw(gameWindow);
	}

	//draw foreground
	for (BackgroundSprite* sprite : foregroundSprites)
	{
		gameWindow.draw(*sprite->GetSprite());
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

	for (auto tile : flowerTiles)
	{
		delete tile;
	}

	for (auto sprite : backgroundSprites)
	{
		delete sprite;
	}

	for (auto sprite : foregroundSprites)
	{
		delete sprite;
	}

	delete userInterface;
	delete soundManager;
}