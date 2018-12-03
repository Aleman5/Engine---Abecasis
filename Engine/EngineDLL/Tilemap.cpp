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
	tileWidth(tWidth), tileHeight(tHeight), tilesetColumns(tColumns), tilesetRows(tRows),
	levelWidth(levelWidth), levelHeight(levelHeight)
{
	levelColumns = (int) (levelWidth / tileWidth);
	levelRows	 = (int) (levelHeight / tileHeight);

	header = TextureImporter::loadBMP_custom(tilesetPath);

	unsigned int windowWidht  = renderer->GetWindowWidht();
	unsigned int windowHeight = renderer->GetWindowHeight();

	activeTilesColumns = (windowWidht % tileWidth == 0)   ? windowWidht / tileWidth   : windowWidht / tileWidth + 1;
	activeTilesRows	   = (windowHeight % tileHeight == 0) ? windowHeight / tileHeight : windowHeight / tileHeight + 1;

	int totalActiveTiles = activeTilesRows * activeTilesColumns;

	vector<vector<Tile>> newVec (activeTilesRows, vector<Tile>(activeTilesColumns));
	activeTiles = newVec;

	level = LoadLevel(levelPath);
	tiles = LoadTiles();
	uvBufferData = GenerateUvForBuffer();

	int totalTiles = activeTilesRows * activeTilesColumns;

	float vertexBufferSize = sizeof(float) * totalTiles * countOfVertices * variables;
	vertexBufferData = SetOnScreenTilesVertices();
	vertexBufferId = renderer->GenBuffer(vertexBufferData, vertexBufferSize);

	verticesData = new float[countOfVertices * 3]{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
	};

	//bufferId = SetVertices(verticesData, countOfVertices);

	drawMode = GL_QUADS;
}

Tilemap::~Tilemap()
{
	delete[] verticesData;
	delete[] uvBufferData;
}

vector<vector<int>> Tilemap::LoadLevel(const char* levelPath)
{
	vector<vector<int>> level (levelRows, vector<int> (levelColumns, 0));
	
	ifstream levelFile;

	int total = levelColumns * 2 - 1;

	levelFile.open(levelPath, ios::in);

	if (!levelFile.good()) printf("Impossible to open Level file: %s\n", levelPath);

	char ch[BUFFER_SIZE];
	int row = 0;
	int value = 0;

	levelFile.getline(ch, total+1);

	while (row < levelRows)
	{
		value = (int)ch[0] - (int)'0';
		level[row][0] = value;

		for (int i = 2; i < total; i += 2)
		{
			value = (int)ch[i] - (int)'0';
			level[row][i/2] = value;
		}
		row++;
		levelFile.getline(ch, total+1);
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

float* Tilemap::GenerateUvForBuffer()
{
	int totActiveTiles = activeTilesRows * activeTilesColumns;

	float* temp = new float[countOfVertices * 2 * totActiveTiles];

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
				temp[counter] = defaultUvVertices[i];

	return temp;
}

float* Tilemap::SetOnScreenTilesVertices()
{
	int totalTiles = activeTilesRows * activeTilesColumns;

	float* vertexBufferData = new float[countOfVertices * variables * totalTiles];

	int counter = 0;

	for (int y = 0; y < activeTilesRows; y++)
		for (int x = 0; x < activeTilesColumns; x++)
		{
			float minX = x * tileWidth;
			float maxX = x * tileWidth + tileWidth;
			float minY = (float)renderer->GetWindowHeight() - (float)(y * tileHeight + tileHeight);
			float maxY = (float)renderer->GetWindowHeight() - (float)(y * tileHeight);

			float vertices[12] =
			{
				minX, minY, 0.0f,
				minX, maxY, 0.0f,
				maxX, maxY, 0.0f,
				maxX, minY, 0.0f
			};

			for (int i = 0; i < countOfVertices * variables; i++, counter++)
				vertexBufferData[counter] = vertices[i];
		}

	return vertexBufferData;
}

void Tilemap::UpdateUV()
{
	int totalTiles = activeTilesRows * activeTilesColumns;
	int uvBufferSize = sizeof(float) * countOfVertices * 2 * totalTiles;
	int counter = 0;

	glm::vec2 offset(GetRenderer()->GetCameraPosition().x / tileWidth, GetRenderer()->GetCameraPosition().y / tileHeight);

	for (int row = 0; row < activeTilesRows; row++)
	{
		for (int column = 0; column < activeTilesColumns; column++)
		{
			Tile tempTile = GetTile(level[row + (int)offset.y][column + (int)offset.x]);
			
			activeTiles[row][column].type = tempTile.type;
			for (int i = 0; i < countOfVertices * 2; i++, counter++)
				uvBufferData[counter] = tempTile.uvData[i];
		}
	}

	uvBufferId = renderer->GenBuffer(uvBufferData, uvBufferSize);
}

void Tilemap::SetTileProperty(unsigned int index, TileType type)
{
	if (index >= tilesetColumns * tilesetRows)
	{
		printf("Index is out of range. The Tile tried to found doesn't exist");
		return;
	}

	unsigned int row = (int)(index / tilesetColumns);
	unsigned int column = (index % tilesetColumns);

	tiles[row][column].type = type;
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
	renderer->BindBuffer(vertexBufferId, 0);
	renderer->BindTextureBuffer(uvBufferId, 1);
	renderer->DrawBuffer(0, countOfVertices * tilesetColumns * tilesetRows, drawMode);
	renderer->DisableAttributes(0);
	renderer->DisableAttributes(1);
}

void Tilemap::ShouldDispose()
{
	if (shouldDispose)
	{
		renderer->DestroyBuffer(bufferId);
		delete[] vertexBufferData;
		shouldDispose = false;
	}
}

unsigned int Tilemap::SetVertices(float* vertices, int count)
{
	//vertexBufferData = vertices;

	unsigned int id = renderer->GenBuffer(vertexBufferData, sizeof(float) * count * variables);
	shouldDispose = true;

	return id;
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

bool Tilemap::IsColliding(glm::vec3 spritePos, glm::vec3& tilePos)
{
	/*
		Hacer los cálculos teniendo en base la posición del sprite y
		la distancia desde el "origen" (a definir) del Tilemap multiplicada por el tamaño de cada Tile.
		(Estoy cansado, es probable que no entienda lo que escribí)
		Tmb es probable que necesite usar la posición de los activeTiles como referencia.
		Para sacar la columna se puede hacer lo mismo pero al revés.
		Solo puede colisionar con un Tile a la vez, por eso devuelve solo un glm::vec3.

		Explicarle al profe que los inputs serían solo en vertical u horizontal,
		nunca ambos (al mismo tiempo).

		row = 
		column = 

		actualTiles[row][column]; // Mmmm... creo que así no es :/

	*/

	return false;
}