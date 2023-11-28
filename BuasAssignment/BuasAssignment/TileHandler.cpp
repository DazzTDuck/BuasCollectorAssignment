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
	{Empty, {0, 0, 0, 0 }},
	{Grass_Begin, {0, 16, 16, 16}},
	{Grass_MiddleA, {16, 16, 16, 16}},
	{Grass_MiddleB, {32, 16, 16, 16}},
	{Grass_MiddleC, {48, 16, 16, 16}},
	{Grass_End, {64, 16, 16, 16}},
	{Invis_Collider, {80, 0, 16 ,16}},
	{Coin, {0, 0, 0, 0}},
	{Rocks_EdgeL1, {0, 32, 16, 16}},
	{Rocks_EdgeL2, {0, 48, 16, 16}},
	{Rocks_EdgeCornerL, {0, 64, 16, 16}},
	{Rocks_EdgeR1, {64, 32, 16, 16}},
	{Rocks_EdgeR2, {64, 48, 16, 16}},
	{Rocks_EdgeCornerR, {64, 64, 16, 16}},
	{Rocks_Empty, {16, 48, 16, 16}},
	{Rocks_Small, {16, 32, 16, 16}},
	{Rocks_Normal, {32, 32, 16, 16}},
	{Rocks_Big, {48, 32, 16, 16}},
	{Rocks_UnderA, {16, 64, 16, 16}},
	{Rocks_UnderB, {32, 64, 16, 16}},
	{Rocks_UnderC, {48, 64, 16, 16}},
	{GrassTop_Begin, {0, 0, 16, 16}},
	{GrassTop_MiddleA, {16, 0, 16, 16}},
	{GrassTop_MiddleB, {32, 0, 16, 16}},
	{GrassTop_MiddleC, {48, 0, 16, 16}},
	{GrassTop_End, {64, 0, 16, 16}},
};

