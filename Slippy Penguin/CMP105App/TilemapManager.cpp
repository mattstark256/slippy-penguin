#include "TilemapManager.h"

#include <iostream>
#include "Framework/Collision.h"

#define TILE_SIZE sf::Vector2f(16, 16)
#define TILEMAP_TEXTURE_FILE_PATH "gfx/Tilemap.png"
#define WATER_TEXTURE_FILE_PATH "gfx/Water.png"
#define BORDER_SIZE sf::Vector2f(128, 128)


TilemapManager::TilemapManager()
{
	if (!tilemapTexture.loadFromFile(TILEMAP_TEXTURE_FILE_PATH))
	{
		std::cout << "Unable to load " << TILEMAP_TEXTURE_FILE_PATH << std::endl;
	}
	if (!waterTexture.loadFromFile(WATER_TEXTURE_FILE_PATH))
	{
		std::cout << "Unable to load " << WATER_TEXTURE_FILE_PATH << std::endl;
	}

	tileWater.setSize(TILE_SIZE);
	tileSnow.setSize(TILE_SIZE);
	tileSnowCliff.setSize(TILE_SIZE);
	tileIce.setSize(TILE_SIZE);
	tileIceCliff.setSize(TILE_SIZE);

	tileWater.setTexture(&tilemapTexture);
	tileWater.setTextureRect(sf::IntRect(55, 1, 16, 16));

	tileSnow.setTexture(&tilemapTexture);
	tileSnow.setTextureRect(sf::IntRect(1, 1, 16, 16));
	tileSnow.setCollisionBox(0, 0, 16, 16);
	tileSnow.setCollisionTag(1);

	tileSnowCliff.setTexture(&tilemapTexture);
	tileSnowCliff.setTextureRect(sf::IntRect(1, 19, 16, 16));

	tileIce.setTexture(&tilemapTexture);
	tileIce.setTextureRect(sf::IntRect(19, 1, 16, 16));
	tileIce.setCollisionBox(0, 0, 16, 16);
	tileIce.setCollisionTag(2);

	tileIceCliff.setTexture(&tilemapTexture);
	tileIceCliff.setTextureRect(sf::IntRect(1, 37, 16, 16));

	std::vector<GameObject> tileset;
	tileset.push_back(tileWater);
	tileset.push_back(tileSnow);
	tileset.push_back(tileSnowCliff);
	tileset.push_back(tileIce);
	tileset.push_back(tileIceCliff);
	tileMap.setTileSet(tileset);

	// Set up the background water
	waterTexture.setRepeated(true);
	background.setTexture(&waterTexture);
	background.setPosition(-BORDER_SIZE);
}


TilemapManager::~TilemapManager()
{
}


// Generate a tilemap from an image texture. The colours of the image are used to determine which tiles should be generated.
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

			// Check if it's a cliff tile
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

	background.setSize((sf::Vector2f)(mapDimensions) * 16.f + BORDER_SIZE * 2.f);
	background.setTextureRect(sf::IntRect(0, 0, background.getSize().x, background.getSize().y));
}


void TilemapManager::render(sf::RenderWindow* window)
{
	window->draw(background);

	tileMap.render(window);
}


// I tried using an AnimatedTile class inheriting from GameObject for each inherited tile. However, there seemed to be an issue with calling the overridden update function. I think Framework/TileMap.h casts any tiles to GameObject, meaning classes inheriting from GameObject just become GameObject. Hence I've had to do the animation here.
void TilemapManager::animateTiles(float dt)
{
	cliffWaterCycleTimer += dt / cliffWaterCycleDuration;
	if (cliffWaterCycleTimer > 1) --cliffWaterCycleTimer;

	for (int y = 0; y < tileMap.getMapSize().y; y++)
	{
		for (int x = 0; x < tileMap.getMapSize().x; x++)
		{
			GameObject* tile = &((*tileMap.getLevel())[y * tileMap.getMapSize().x + x]);

			// I've just used the vertical position of the texture rect to determine the type of a tile. This remains constant because the animation frames are positioned horizonally.
			if (tile->getTextureRect().top == 19 || tile->getTextureRect().top == 37)
			{
				// X position is taken into account when calculating frame. This means horizontally adjacent tiles are out of sync with each other, giving the effect of ripples moving from right to left. 
				int frame = (int)(cliffWaterCycleTimer * 6 + x) % 6;
				tile->setTextureRect(sf::IntRect(1 + 18 * frame, tile->getTextureRect().top, 16, 16));
			}
		}
	}

	// Loop through 4 frames
	backgroundCycleTimer += dt / backgroundCycleDuration;
	if (backgroundCycleTimer > 1) --backgroundCycleTimer;
	int frame = (int)(backgroundCycleTimer * 4) % 4;
	background.setTextureRect(sf::IntRect(0, 32 * frame, background.getTextureRect().width, background.getTextureRect().height));

}


// Convert a position to tile coordinates. This can be used in conjunction with getTile, because it requires the tile coordinates.
sf::Vector2i TilemapManager::pointToTileCoords(sf::Vector2f point)
{
	return (sf::Vector2i)(point * (1.f/16));
}


// Gets the tile object at the specified tile coordinates.
GameObject* TilemapManager::getTile(sf::Vector2u tileCoords)
{
	if (tileCoords.x > tileMap.getMapSize().x || tileCoords.y > tileMap.getMapSize().y) { return nullptr; }
	return &((*tileMap.getLevel())[tileCoords.y * tileMap.getMapSize().x + tileCoords.x]);
}
