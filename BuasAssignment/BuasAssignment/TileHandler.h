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
	Invis_Collider
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

