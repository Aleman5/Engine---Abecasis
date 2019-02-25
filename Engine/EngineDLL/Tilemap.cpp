#include "Tilemap.h"

Tilemap::Tilemap(
	Renderer* renderer,				// Renderer reference
	Material* material,				// Material reference
	Layers layer,					// Layer of the Entity
	const char* tilesetPath,		// Path of the Tileset
	const unsigned int tColumns,	// Columns on the Tileset
	const unsigned int tRows,		// Rows on the Tileset
	const char* levelPath,			// Path of the Level
	const unsigned int levelWidth,	// Width of the Level
	const unsigned int levelHeight	// Height of the Level
) : Entity(renderer, material, layer),
tilesetColumns(tColumns), tilesetRows(tRows),
levelWidth(levelWidth), levelHeight(levelHeight),
texturePath(tilesetPath)
{
	header = TextureImporter::loadBMP_custom(texturePath);
	textureId = renderer->GenTilemapTexture(header.width, header.height, header.data);

	tileWidth = header.width / tilesetColumns;
	tileHeight = header.height / tilesetRows;

	levelColumns = (int)(levelWidth / (header.width / tColumns));
	levelRows	 = (int)(levelHeight / (header.height / tRows));

	unsigned int windowWidth = renderer->GetWindowWidht();
	unsigned int windowHeight = renderer->GetWindowHeight();

	activeTilesColumns = (windowWidth % tileWidth == 0) ? windowWidth / tileWidth : windowWidth / tileWidth + 1;
	activeTilesRows = (windowHeight % tileHeight == 0) ? windowHeight / tileHeight : windowHeight / tileHeight + 1;

	lastRowOffset = windowHeight % tileHeight;
	lastColumnOffset = windowWidth % tileWidth;

	int totalActiveTiles = activeTilesRows * activeTilesColumns;

	//vector<vector<Tile>> newVec(activeTilesRows, vector<Tile>(activeTilesColumns));
	//activeTiles = newVec;
	/*Tile hi;
	hi.type = TileType::Background;
	activeTiles[1][1] = hi;*/
	level = LoadLevel(levelPath);
	/*for (int i = 0; i < levelRows; i++)
	{
		for (int j = 0; j < levelColumns; j++)
		{
			cout << level[i][j] << " ";
		}
		cout << endl;
	}*/
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

	bufferId = SetVertices(verticesData, countOfVertices);

	drawMode = GL_QUADS;
}

Tilemap::~Tilemap()
{
	delete[] verticesData;
	delete[] uvBufferData;
}

vector<vector<int>> Tilemap::LoadLevel(const char* levelPath)
{
	/*vector<vector<int>> level (levelRows, vector<int> (levelColumns, 0));
	
	ifstream levelFile;

	int total = levelColumns * 2;

	levelFile.open(levelPath, ios::in);

	if (!levelFile.good()) printf("Impossible to open Level file: %s\n", levelPath);

	char ch[BUFFER_SIZE];
	int row = 0;
	int value = 0;

	levelFile.getline(ch, total);

	while (row < levelRows)
	{
		value = (int)ch[0] - (int)'0';
		level[row][0] = value;

		for (int i = 2; i < total; i += 2)
		{
			value = (int)ch[i] - (int)'0';
			level[row][i/2] = value;
			cout << level[row][i / 2] << " ";
		}
		cout << endl;
		row++;
		levelFile.getline(ch, total);
	}*/

	std::ifstream levelFile;
	
	vector<vector<int>> level(levelRows, vector<int>(levelColumns, 0));

	char buffer[BUFFER_SIZE];

	float rows = levelRows;
	float columns = levelColumns;

	//levelRows = (levelHeight % Tile::height == 0) ? rows : rows + 1;
	//levelColumns = (levelWidth % Tile::width == 0) ? columns : columns + 1;

	levelFile.open(levelPath, std::ios::in);

	if (!levelFile.good())
		throw std::ios::failure("The level file could not be opened.");

	levelFile.getline(buffer, BUFFER_SIZE);
	levelFile.get(buffer, BUFFER_SIZE, '>');
	levelFile.get();
	memset(buffer, 0, sizeof(buffer));

	int x = 0;
	int y = 0;
	int nextChar = levelFile.peek();

	while (isdigit(nextChar) && !levelFile.eof())
	{
		if (x < levelColumns - 1)
			levelFile.get(buffer, BUFFER_SIZE, ',');
		else
		{
			if (y < levelRows - 1)
				levelFile.get(buffer, BUFFER_SIZE, '\n');
			else
				levelFile.get(buffer, BUFFER_SIZE, ',');
		}

		int digits = 0;
		int value = 0;

		for (int i = 0; buffer[i] != '\0'; i++)
			digits++;
		for (int i = 0; i < digits; i++)
			value += ((int)buffer[i] - (int)'0') * pow(10, digits - 1 - i);

		level[y][x] = value;
		cout << value << " ";
		if (x < levelColumns - 1)
			x++;
		else
		{
			x = 0;
			y++;
			cout << endl;
		}
		levelFile.get();
		nextChar = levelFile.peek();
	}

	return level;
}

vector<vector<Tile>> Tilemap::LoadTiles()
{
	vector<vector<Tile>> tiles(tilesetRows, vector<Tile>(tilesetColumns));

	for (int y = 0; y < tilesetRows; y++)
		for (int x = 0; x < tilesetColumns; x++)
		{
			tiles[y][x].index = x + y * tilesetColumns;
			tiles[y][x].type = Background;

			float minU =		(float) (x * tileWidth				) / (float) header.width;
			float maxU =		(float) (x * tileWidth + tileWidth	) / (float) header.width;
			float minV = 1.0f - (float) (y * tileHeight	+ tileHeight) / (float) header.height;
			float maxV = 1.0f - (float) (y * tileHeight				) / (float) header.height;

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
	int uvBufferSize = sizeof(float) * countOfVertices * 2 * activeTilesRows * activeTilesColumns;
	int counter = 0;

	glm::vec2 tilingOffset((int)renderer->GetCameraPosition().x / tileWidth, (int)renderer->GetCameraPosition().y / tileHeight);
	int lastRow = (int)levelHeight / (int)tileHeight - 1;
	int lastColumn = (int)levelWidth / (int)tileWidth - 1;

	/*cout << "Tile [0][0]" << tiles[0][0].type << endl;
	cout << "Tile [0][1]" << tiles[0][1].type << endl;
	cout << "Tile [1][0]" << tiles[1][0].type << endl;
	cout << "Tile [1][1]" << tiles[1][1].type << endl;
	cout << "Tile [2][0]" << tiles[2][0].type << endl;
	cout << "Tile [2][1]" << tiles[2][1].type << endl;*/

	/*for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << "Tile [" << i << "][" << j << "]: ";
			for (int k = 0; k < 8; k++)
			{
				if (k % 2 == 0) cout << "           ";
				cout << tiles[i][j].uvData[k] << " ";
			}
			cout << endl;
		}
	}*/

	for (int y = 0; y < activeTilesRows; y++)
	{
		//cout << "[" << y << "]: ";
		for (int x = 0; x < activeTilesColumns; x++)
		{
			int levelRow = min(y + (int)tilingOffset.y, lastRow);
			int levelColumn = min(x + (int)tilingOffset.x, lastColumn);
			
			Tile tile = GetTile(level[levelRow][levelColumn]);

			//cout /*<< "[" << y << "][" << x << "]: "*/ << tile.index << " ";

			//activeTiles[y][x].type = tile.type;
			//activeTiles[y][x].uvData = tile.uvData;
			for (int i = 0; i < countOfVertices * 2; i++, counter++)
			{
				uvBufferData[counter] = tile.uvData[i];
				//cout << uvBufferData[counter] << " ";
			}
			//cout << endl;
		}
		//cout << endl;
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

	unsigned int row	= index / tilesetColumns;
	unsigned int column = index % tilesetColumns;

	tiles[row][column].type = type;
	
	cout << "Real Index: " << index << "; Tile Index: " << tiles[row][column].index << "; Type: " <<  tiles[row][column].type << endl;

	/*glm::vec2 tilingOffset((int)GetPosition().x / tileWidth, (int)GetPosition().y / tileHeight);
	int lastRow = (int)levelHeight / (int)tileHeight - 1;
	int lastColumn = (int)levelWidth / (int)tileWidth - 1;

	for (int y = 0; y < activeTilesRows; y++)
		for (int x = 0; x < activeTilesColumns; x++)
		{
			int levelRow = min(y + (int)tilingOffset.y, lastRow);
			int levelColumn = min(x + (int)tilingOffset.x, lastColumn);

			if (level[levelRow][levelColumn] == index)
			{
				activeTiles[y][x].type = tiles[row][column].type;
				activeTiles[y][x].uvData = tiles[row][column].uvData;
			}
		}*/
}

void Tilemap::Draw()
{
	renderer->loadIdentityMatrix();
	renderer->SetModelMatrix(model);
	
	if (material != NULL)
	{
		material->Bind(texturePath, textureId);
		material->SetMatrixProperty("MVP", renderer->GetMVP());
	}

	renderer->EnableBlend();

	renderer->EnableAttributes(0);
	renderer->EnableAttributes(1);
	renderer->BindBuffer(vertexBufferId, 0);
	renderer->BindTextureBuffer(uvBufferId, 1);
	renderer->DrawBuffer(0, countOfVertices * activeTilesColumns * activeTilesRows, drawMode);
	renderer->DisableAttributes(0);
	renderer->DisableAttributes(1);

	renderer->DisableBlend();
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
	unsigned int row	= pos / tilesetColumns;

	/*for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cout << "[" << i << "][" << j << "] " << tiles[i][j].type << endl;

		}
	}*/

	return tiles[row][column];
}

TileType Tilemap::GetTileType(unsigned int row, unsigned int column)
{
	return GetTile(level[row][column]).type;
}

glm::vec2 Tilemap::WorldToGrid(float posY, float posX)
{
	unsigned int row = (levelRows - 1) - (int)posX / tileHeight;
	unsigned int col = posY / tileWidth;

	return glm::vec2(row, col);
}

glm::vec2 Tilemap::GridToWorld(unsigned int row, unsigned int col)
{
	float posY = -((int)(row - levelRows + 1) * (int)tileHeight) + lastRowOffset;
	float posX = col * tileWidth;

	return glm::vec2(posX, posY);
}

TilesAround Tilemap::GetAroundTiles(glm::vec3 spritePos)
{
	/*
		Preguntar a partir de la posicion del sprite, en qué tile está, de ahí devolver los cuatro tiles
		de las 4 direcciones (up, down, left, right). Después dentro del sprite calcular la colisión con
		esos 4 tiles sólo si son obstáculos.
	*/

	TilesAround tileCol = TilesAround();

	return tileCol;
}