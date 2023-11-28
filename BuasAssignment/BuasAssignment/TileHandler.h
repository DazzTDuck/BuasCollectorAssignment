#pragma once

#include "TileObject.h"

enum TileTypes
{
	Empty,
	Grass_Begin,
	Grass_MiddleA,
	Grass_MiddleB,
	Grass_MiddleC,
	Grass_End,
	Invis_Collider,
	Coin,
	Rocks_EdgeL1,
	Rocks_EdgeL2,
	Rocks_EdgeCornerL,
	Rocks_EdgeR1,
	Rocks_EdgeR2,
	Rocks_EdgeCornerR,
	Rocks_Small,
	Rocks_Normal,
	Rocks_Big,
	Rocks_Empty,
	Rocks_UnderA,
	Rocks_UnderB,
	Rocks_UnderC,
	GrassTop_Begin,
	GrassTop_MiddleA,
	GrassTop_MiddleB,
	GrassTop_MiddleC,
	GrassTop_End,
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

