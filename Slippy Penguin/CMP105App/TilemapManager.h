#pragma once

#include "Framework/TileMap.h"


// This class acts as an interface for the Tilemap class. It also handles the water surrounding the tilemap.
class TilemapManager
{
public:
	TilemapManager();
	~TilemapManager();

	void generateTilemap(std::string imageFilepath);
	void render(sf::RenderWindow* window);
	void animateTiles(float dt);
	sf::Vector2i pointToTileCoords(sf::Vector2f point);
	GameObject* getTile(sf::Vector2u tileCoords);

private:
	TileMap tileMap;
	sf::Texture tilemapTexture;
	sf::Texture waterTexture;

	GameObject tileWater;
	GameObject tileSnow;
	GameObject tileSnowCliff;
	GameObject tileIce;
	GameObject tileIceCliff;

	// Background water
	GameObject background;

	// cliff tile animation variables
	float cliffWaterCycleTimer;
	float cliffWaterCycleDuration = 1.2;

	// background animation variables
	float backgroundCycleTimer;
	float backgroundCycleDuration = 1.2;
};

