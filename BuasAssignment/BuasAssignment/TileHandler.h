#pragma once

#include "TileObject.h"

enum TileTypes
{
	Empty,
	Grass_Begin,
	Grass_MiddleA,
	Grass_MiddleB,
	Grass_MiddleC,
	Grass_End, // 5
	Invis_Collider,
	Coin,
	Rocks_EdgeL1,
	Rocks_EdgeL2,
	Rocks_EdgeCornerL, // 10
	Rocks_EdgeR1,
	Rocks_EdgeR2,
	Rocks_EdgeCornerR,
	Rocks_Small,
	Rocks_Normal, // 15
	Rocks_Big,
	Rocks_Empty,
	Rocks_UnderA,
	Rocks_UnderB,
	Rocks_UnderC, // 20
	GrassTop_Begin,
	GrassTop_MiddleA,
	GrassTop_MiddleB,
	GrassTop_MiddleC,
	GrassTop_End, // 25
	Rock_Begin,
	Rock_MiddleA,
	Rock_MiddleB,
	Rock_MiddleC,
	Rock_End, // 30
	RockTop_Begin,
	RockTop_MiddleA,
	RockTop_MiddleB,
	RockTop_MiddleC,
	RockTop_End, // 35
	Bridge_Begin,
	Bridge_MiddleA,
	Bridge_MiddleB,
	Bridge_MiddleC,
	Bridge_End, // 40
	BridgeTop_Begin,
	BridgeTop_MiddleA,
	BridgeTop_MiddleB,
	BridgeTop_MiddleC,
	BridgeTop_End, // 45
	RockGrass_Begin,
	RockGrass_End,
	RockGrassTop_Begin,
	RockGrassTop_End,
	Chest, // 50
	Bridge_ExtraA,
	Bridge_ExtraB,
	Bridge_ExtraC,
	BridgeTop_ExtraA,
	BridgeTop_ExtraB, //55
	BridgeTop_ExtraC,
	Mushroom_A,
	Mushroom_B,
	GrassPiece,
	Flower_A, //60
	Flower_B,
	Flower_C,
	Snail,
	Boar,
	Player

};

class TileHandler
{
public:
	TileHandler();

	TileObject* CreateNewTile(sf::Vector2f position, TileTypes tileType);

	static const std::map<TileTypes, sf::IntRect> tileDefinitions;

private:

	sf::Texture _tileTexture;
};

