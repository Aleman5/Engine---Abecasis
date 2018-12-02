#include "Tilemap.h"

Tilemap::Tilemap(
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
) : Entity(renderer, material, layer),
	levelWidth(levelWidth), levelHeight(levelHeight), levelColumns(levelWidth / tileWidth), levelRows(levelHeight / tileHeight),
	tileWidth(), tileHeight(), tilesetColumns(tColumns), tilesetRows(tRows)
{
	header = TextureImporter::loadBMP_custom(tilesetPath);

	unsigned int windowWidht  = renderer->GetWindowWidht();
	unsigned int windowHeight = renderer->GetWindowHeight();

	activeTilesColumns = (windowWidht % tileWidth == 0)   ? windowWidht / tileWidth   : windowWidht / tileWidth + 1;
	activeTilesRows	   = (windowHeight % tileHeight == 0) ? windowHeight / tileHeight : windowHeight / tileHeight + 1;

	level = LoadLevel(levelPath);
	tiles = LoadTiles();
	GenerateUvForBuffer();

	drawMode = GL_QUADS;
}

Tilemap::~Tilemap()
{
	delete[] uvBufferData;
}

vector<vector<int>> Tilemap::LoadLevel(const char* levelPath)
{
	vector<vector<int>> level (levelRows, vector<int> (levelColumns, 0));
	
	ifstream levelFile;
	char buffer[BUFFER_SIZE];

	levelFile.open(levelPath, ios::in);

	if (!levelFile.good()) printf("Impossible to open Level file: %s\n", levelPath);

	levelFile.getline(buffer, BUFFER_SIZE);
	levelFile.get(buffer, BUFFER_SIZE, '>');
	levelFile.get();
	memset(buffer, 0, sizeof(buffer));

	int row = 0;
	int column = 0;
	int nextChar = levelFile.peek();

	while (isdigit(nextChar) && !levelFile.eof())
	{
		if (column < tilesetColumns - 1)
		{
			levelFile.get(buffer, BUFFER_SIZE, ',');
		}
		else
		{
			if (row < tilesetRows - 1)
				levelFile.get(buffer, BUFFER_SIZE, '\n');
			else
				levelFile.get(buffer, BUFFER_SIZE, '<');
		}

		int digits = 0;
		int value = 0;

		for (int i = 0; buffer[i] != '\0'; i++)
			digits++;
		for (int i = 0; i < digits; i++)
			value += ((int)buffer[i] - (int)'0') * pow(10, digits - 1 - i);

		level[row][column] = value;

		if (column < tilesetColumns - 1)
		{
			column++;
		}
		else
		{
			column = 0;
			row++;
		}
		levelFile.get();
		nextChar = levelFile.peek();
	}
	return level;
}

vector<vector<Tile>> Tilemap::LoadTiles()
{
	Tile tileDefault;

	vector<vector<Tile>> tiles(tilesetRows, vector<Tile>(tilesetColumns, tileDefault));

	for (int y = 0; y < tilesetRows; y++)
		for (int x = 0; x < tilesetColumns; x++)
		{
			float minU =		(float) (x * tileWidth				) / (float) header.width;
			float maxU =		(float) (x * tileWidth + tileWidth	) / (float) header.width;
			float minV = 1.0f - (float) (y * tileHeight				) / (float) header.height;
			float maxV = 1.0f - (float) (y * tileHeight	+ tileHeight) / (float) header.height;

			float* uvData = new float[8]
			{
				minU, minV,
				minU, maxV,
				maxU, maxV,
				maxU, minV
			};

			tiles[y][x].uvData = uvData;
		}

	return tiles;
}

vector<vector<Tile>> Tilemap::CreateOnScreenTiles()
{
	Tile tileDefault;

	vector<vector<Tile>> onScreenTiles(activeTilesRows, vector<Tile>(activeTilesColumns, tileDefault));

	int totalTiles = activeTilesRows * activeTilesColumns;

	float vertexBufferSize = sizeof(float) * totalTiles * countOfVertices * variables;

	//vertexBufferData = SetOnScreenTilesVertices(totalTiles); // ------ WIP ------
	vertexBufferId = renderer->GenBuffer(vertexBufferData, vertexBufferSize);

	return onScreenTiles;
}

void Tilemap::GenerateUvForBuffer()
{
	int totalActiveTiles = activeTilesRows * activeTilesColumns;

	uvBufferData = new float[countOfVertices * 2 * totalActiveTiles];

	float defaultUvVertices[8] =
	{
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};

	int counter = 0;

	for (int y = 0; y < activeTilesRows; y++)
		for (int x = 0; x < activeTilesColumns; x++)
			for (int i = 0; i < countOfVertices * 2; i++, counter++)
				uvBufferData[counter] = defaultUvVertices[i];

	UpdateUV();
}

void Tilemap::UpdateUV()
{
	int totalTiles = activeTilesRows * activeTilesColumns;
	int uvBufferSize = sizeof(float) * countOfVertices * 2 * totalTiles;

	int counter = 0;

	for (int row = 0; row < activeTilesRows; row++)
		for (int column = 0; column < activeTilesColumns; column++)
		{
			//glm::vec2 offset(cameraPosition.x / tileWidth, cameraPosition.y / tileHeight);
			glm::vec2 offset(0.0f, 0.0f);														// ------ WIP ------
			Tile tile = GetTile(level[row + (int)offset.y][column + (int)offset.x]);

			activeTiles[row][column].type = tile.type;
			for (int i = 0; i < countOfVertices * 2; i++, counter++)
				uvBufferData[counter] = tile.uvData[i];
		}

	uvBufferId = renderer->GenBuffer(uvBufferData, uvBufferSize);
}

void Tilemap::Draw()
{
	renderer->loadIdentityMatrix();
	renderer->SetModelMatrix(model);

	if (material != NULL)
	{
		material->Bind();
		material->SetMatrixProperty("MVP", renderer->GetMVP());
	}

	renderer->EnableAttributes(0);
	renderer->EnableAttributes(1);
	renderer->BindBuffer(bufferId, 0);
	renderer->BindTextureBuffer(uvBufferId, 1);
	renderer->DrawBuffer(0, countOfVertices * tilesetColumns * tilesetRows, drawMode);
	renderer->DisableAttributes(0);
	renderer->DisableAttributes(1);
}

Tile Tilemap::GetTile(unsigned int pos)
{
	if (pos >= tilesetRows * tilesetColumns)
	{
		printf("The position (%s) tried to found is out of range.", pos);
		return Tile();
	}

	unsigned int column = pos % tilesetColumns;
	unsigned int row	= pos / tilesetRows;

	return tiles[row][column];
}