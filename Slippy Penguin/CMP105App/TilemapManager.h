#pragma once

#include "Framework/TileMap.h"


// This class acts as an interface for the Tilemap class.
class TilemapManager
{
public:
	TilemapManager();
	~TilemapManager();

	void generateTilemap(std::vector<int> tm, sf::Vector2u mapDimensions);
	void generateTilemap(std::string imageFilepath);
	void render(sf::RenderWindow* window);
	sf::Vector2i pointToTileCoords(sf::Vector2f point);
	GameObject* getTile(sf::Vector2u tileCoords);

private:
	TileMap tileMap;
	sf::Texture texture;

	GameObject tileWater;
	GameObject tileSnow;
	GameObject tileSnowCliff;
	GameObject tileIce;
	GameObject tileIceCliff;
};

