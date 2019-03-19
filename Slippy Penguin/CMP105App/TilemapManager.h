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
	bool checkForGround(GameObject* gameObject);
	bool checkForIce(GameObject* gameObject);
	bool checkForCliff(GameObject* gameObject);

private:
	TileMap tileMap;
	sf::Texture texture;

	GameObject tileWater;
	GameObject tileSnow;
	GameObject tileSnowCliff;
	GameObject tileIce;
	GameObject tileIceCliff;

	bool checkForCollisionWithTag(GameObject* gameObject, int tag);
};

