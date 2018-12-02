#pragma once

#include "Exports.h"
#include "Entity.h"
#include "TextureImporter.h"

#define BUFFER_SIZE 64

enum TileType
{
	Obstacle,
	Background,
	Trigger
};

struct Tile
{
	TileType type;
	float* uvData;
};

class ENGINEDLL_API Tilemap : public Entity
{
	Header header;

	unsigned int uvBufferId;
	unsigned int vertexBufferId;
	float* uvBufferData;
	float* vertexBufferData;

	vector<vector<int>> level;
	vector<vector<Tile>> tiles;
	vector<vector<Tile>> activeTiles;

	const unsigned int countOfVertices = 4;
	const unsigned int variables = 3;

	unsigned int levelColumns;
	unsigned int levelRows;
	unsigned int levelWidth;
	unsigned int levelHeight;

	unsigned int tilesetColumns;
	unsigned int tilesetRows;
	unsigned int tileWidth;
	unsigned int tileHeight;

	unsigned int activeTilesColumns;
	unsigned int activeTilesRows;

	

	vector<vector<int>> LoadLevel(const char* levelPath);
	vector<vector<Tile>> CreateOnScreenTiles();
	void GenerateUvForBuffer();

	vector<vector<Tile>> LoadTiles();

public:
	void Draw() override;
	void UpdateUV();

	Tile GetTile(unsigned int pos);

	Tilemap(
		Renderer* renderer,				// Renderer reference
		Material* material,				// Material reference
		Layers layer,					// Layer of the Entity
		const char* tilesetPath,		// Path of the Tileset
		const unsigned int tColumns,	// Columns on the Tileset
		const unsigned int tRows,		// Rows on the Tileset
		const unsigned int tWidth,		// Width of each Tileset
		const unsigned int tHeight,		// Height of each Tileset
		const char* levelPath,			// Path of the Level
		const unsigned int levelWidth,	// Width of the Level
		const unsigned int levelHeight	// Height of the Level
	);
	~Tilemap();
};

