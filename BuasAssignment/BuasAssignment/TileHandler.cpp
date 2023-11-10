#include "TileHandler.h"

TileHandler::TileHandler() :
	_tileTexture()
{
	_tileTexture.loadFromFile("Assets/Assets/Tiles.png");
}

TileObject* TileHandler::CreateNewTile(sf::Vector2f position, TileTypes tileType)
{
	sf::Sprite* newSprite = new sf::Sprite();
	newSprite->setTexture(_tileTexture);
	newSprite->setTextureRect(tileDefinitions.at(tileType));
	newSprite->setPosition(position);

	return new TileObject(newSprite);
}


const std::map<TileTypes, sf::IntRect> TileHandler::tileDefinitions = 
{
	{Grass_Begin, { 0, 9 ,16 ,23 }},
	{Grass_MiddleA, { 16, 9 ,16 ,23 }},
	{Grass_MiddleB, { 32, 9 ,16 ,23 }},
	{Grass_MiddleC, { 48, 9 ,16 ,23 }},
	{Grass_End, { 64, 9 ,16 ,23 }}
};

