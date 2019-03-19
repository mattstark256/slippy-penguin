#include "TilemapManager.h"

#include <iostream>
#include "Framework/Collision.h"

#define TILE_SIZE sf::Vector2f(16, 16)
#define TILEMAP_TEXTURE_FILE_PATH "gfx/Tilemap.png"


TilemapManager::TilemapManager()
{
	if (!texture.loadFromFile(TILEMAP_TEXTURE_FILE_PATH))
	{
		std::cout << "Unable to load " << TILEMAP_TEXTURE_FILE_PATH << std::endl;
	}

	tileWater.setSize(TILE_SIZE);
	tileSnow.setSize(TILE_SIZE);
	tileSnowCliff.setSize(TILE_SIZE);
	tileIce.setSize(TILE_SIZE);
	tileIceCliff.setSize(TILE_SIZE);

	tileWater.setTexture(&texture);
	tileWater.setTextureRect(sf::IntRect(1, 37, 16, 16));

	tileSnow.setTexture(&texture);
	tileSnow.setTextureRect(sf::IntRect(1, 1, 16, 16));
	tileSnow.setCollisionBox(0, 0, 16, 16);
	tileSnow.setCollisionTag(1);

	tileSnowCliff.setTexture(&texture);
	tileSnowCliff.setTextureRect(sf::IntRect(1, 19, 16, 16));
	tileIce.setTexture(&texture);
	tileIce.setTextureRect(sf::IntRect(19, 1, 16, 16));
	tileIce.setCollisionBox(0, 0, 16, 16);
	tileIce.setCollisionTag(2);

	tileIceCliff.setTexture(&texture);
	tileIceCliff.setTextureRect(sf::IntRect(19, 19, 16, 16));


	std::vector<GameObject> tileset;
	tileset.push_back(tileWater);
	tileset.push_back(tileSnow);
	tileset.push_back(tileSnowCliff);
	tileset.push_back(tileIce);
	tileset.push_back(tileIceCliff);
	tileMap.setTileSet(tileset);
}


TilemapManager::~TilemapManager()
{
}


void TilemapManager::generateTilemap(std::vector<int> tm, sf::Vector2u mapDimensions)
{
	// Convert water tiles under snow or ice tiles into the corresponding cliff tiles (this saves some effort in making levels)
	for (int i = 0; i < tm.size(); i++)
	{
		int tileAbove = i - (int)mapDimensions.x;
		if (tm[i] == 0 && tileAbove >= 0)
		{
			if (tm[tileAbove] == 1) { tm[i] = 2; }
			if (tm[tileAbove] == 3) { tm[i] = 4; }
		}
	}

	tileMap.setTileMap(tm, mapDimensions);
	tileMap.buildLevel();
}


void TilemapManager::generateTilemap(std::string imageFilepath)
{
	sf::Image image;
	if (!image.loadFromFile(imageFilepath))
	{
		std::cout << "Unable to load " << imageFilepath << std::endl;
		return;
	}

	sf::Vector2u mapDimensions = image.getSize();

	std::vector<int> tiles;

	for (int y = 0; y < mapDimensions.y; y++)
	{
		for (int x = 0; x < mapDimensions.x; x++)
		{
			sf::Color pixelColor = image.getPixel(x, y);
			int tile = 0;
			if (pixelColor == sf::Color::Red) { tile = 1; }
			if (pixelColor == sf::Color::Blue) { tile = 3; }

			if (y > 0 && tile == 0)
			{
				sf::Color pixelAboveColor = image.getPixel(x, y - 1);
				if (pixelAboveColor == sf::Color::Red) { tile = 2; }
				if (pixelAboveColor == sf::Color::Blue) { tile = 4; }
			}

			tiles.push_back(tile);
		}
	}

	tileMap.setTileMap(tiles, mapDimensions);
	tileMap.buildLevel();
}


void TilemapManager::render(sf::RenderWindow* window)
{
	tileMap.render(window);
}


sf::Vector2i TilemapManager::pointToTileCoords(sf::Vector2f point)
{
	return (sf::Vector2i)(point * (1.f/16));
}


GameObject* TilemapManager::getTile(sf::Vector2u tileCoords)
{
	if (tileCoords.x > tileMap.getMapSize().x || tileCoords.y > tileMap.getMapSize().y) { return nullptr; }
	return &((*tileMap.getLevel())[tileCoords.y *tileMap.getMapSize().x + tileCoords.x]);
}
