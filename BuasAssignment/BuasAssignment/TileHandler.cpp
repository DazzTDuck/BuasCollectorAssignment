#include "TileHandler.h"

TileHandler::TileHandler() 
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
	{Rock_Begin, {0, 96, 16, 16}},
	{Rock_MiddleA, {16, 96, 16, 16}},
	{Rock_MiddleB, {32, 96, 16, 16}},
	{Rock_MiddleC, {48, 96, 16, 16}},
	{Rock_End, {64, 96, 16, 16}},
	{RockTop_Begin, {0, 80, 16, 16}},
	{RockTop_MiddleA, {16, 80, 16, 16}},
	{RockTop_MiddleB, {32, 80, 16, 16}},
	{RockTop_MiddleC, {48, 80, 16, 16}},
	{RockTop_End, {64,80, 16, 16}},
	{Bridge_Begin, {80, 144, 16, 16}},
	{Bridge_MiddleA, {96, 144, 16, 16}},
	{Bridge_MiddleB, {112, 144, 16, 16}},
	{Bridge_MiddleC, {128, 144, 16, 16}},
	{Bridge_End, {144, 144, 16, 16}},
	{BridgeTop_Begin, {80, 112, 16, 32}},
	{BridgeTop_MiddleA, {96, 128, 16, 16}},
	{BridgeTop_MiddleB, {112, 128, 16, 16}},
	{BridgeTop_MiddleC, {128, 128, 16, 16}},
	{BridgeTop_End, {144, 112, 16, 32}},
	{RockGrass_Begin, {0, 176, 16, 16}},
	{RockGrass_End, {16, 176, 16, 16}},
	{RockGrassTop_Begin, {0, 160, 16, 16}},
	{RockGrassTop_End, {16, 160, 16, 16}},
	{Chest, {288, 272, 32, 32}},
	{Bridge_ExtraA, {80, 96, 16, 16}},
	{Bridge_ExtraB, {96, 96, 16, 16}},
	{Bridge_ExtraC, {112, 96, 16, 16}},
	{BridgeTop_ExtraA, {80, 80, 16, 16}},
	{BridgeTop_ExtraB, {96, 80, 16, 16}},
	{BridgeTop_ExtraC, {112, 80, 16, 16}},
	{Mushroom_A, {240, 208, 16, 32}},
	{Mushroom_B, {240, 240, 16, 32}},
	{GrassPiece, {352, 272, 16, 32}},
	{Flower_A, {224, 256, 16, 32}},
	{Flower_B, {256, 288, 16, 32}},
	{Flower_C, {256, 320, 16, 32}},
	{SnailEnemy,{0, 0, 0, 0}},
};

