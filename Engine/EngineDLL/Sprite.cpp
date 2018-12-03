#include "Sprite.h"
#include "Tilemap.h"

Sprite::Sprite(
	Renderer* renderer,			 // Renderer reference
	Material* material,			 // Material reference
	Layers layer,				 // Layer of the Entity
	const char* imagePath,		 // Path of the image
	bool isAnimated,			 // Is animated? Yes/No
	const unsigned int sColumns, // Columns of the spritesheet
	const unsigned int sRows, 	 // Rows of the spritesheet
	const float colliderWidth, 	 // Width of the collider
	const float colliderHeight,	 // Height of the collider
	bool isInteractable,		 // Does the Sprite collide with the Tilemap? Yes/No
	Tilemap* tilemap			 // Tilemap reference
)
	: Shape(renderer, material, layer), actualFrame(0), columns(sColumns), rows(sRows),
	  isAnimated(isAnimated), isInteractable(isInteractable), tilemap(tilemap)
{
	count = 4;
	variables = 3;

	verticesData = new float[count * 3]{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
	};

	/*verticesTextureData = new float[count * 2]{
		0.0f, 1.0f - 1.0f,
		1.0f, 1.0f - 1.0f,
		0.0f, 1.0f - 0.0f,
		1.0f, 1.0f - 0.0f,
	};*/

	drawMode = GL_TRIANGLE_STRIP;

	bufferId = SetVertices(verticesData, count);

	header = TextureImporter::loadBMP_custom(imagePath);

	widthOfFrame  = (int) (header.width  / sColumns);
	heightOfFrame = (int) (header.height / sRows);

	textureId = renderer->GenTexture(header.width, header.height, header.data);

	//textureId = SetTextureUV(verticesTextureData, count, 2);

	unsigned int frames[5] = { 5, 6, 7, 8, 9};
	if (isAnimated) anim = new Animation(this, frames, true, 10.0f);
	else SetNewFrame(0);

	col.x = colliderWidth;
	col.y = colliderHeight;
}

Sprite::~Sprite()
{
	delete verticesData;
	if (isAnimated) delete anim;
}

void Sprite::Draw()
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
	renderer->DrawBuffer(0, count, drawMode);
	renderer->DisableAttributes(0);
	renderer->DisableAttributes(1);
}

void Sprite::Update(float deltaTime)
{
	if (isAnimated) anim->Update(deltaTime);

	if (isInteractable) CheckCollisionWithTilemap();
}

unsigned int Sprite::SetTextureUV(float* vertices, int count, int variables)
{
	//verticesData = vertices;

	unsigned int id = renderer->GenBuffer(vertices, sizeof(float) * count * variables);
	shouldDispose = true;

	return id;
}

void Sprite::SetNewFrame(unsigned int newFrame)
{
	actualFrame = newFrame;
	
	unsigned int uvBufferSize = sizeof(float) * count * 2;

	unsigned int u =	  (actualFrame % rows	) * widthOfFrame;
	unsigned int v = (int)(actualFrame / columns) * heightOfFrame;
	
	uvBufferData = SetUV(u, v);

	uvBufferId = renderer->GenBuffer(uvBufferData, uvBufferSize);
}

float* Sprite::SetUV(unsigned int u, unsigned int v)
{
	float minU =		(float)  u					/ header.width;
	float maxU =		(float) (u + widthOfFrame)	/ header.width;
	float minV = 1.0f - (float)  v					/ header.height;
	float maxV = 1.0f - (float) (v + heightOfFrame) / header.height;

	float* bufferData = new float[count * 2]
	{
		minU, maxV,
		maxU, maxV,
		minU, minV,
		maxU, minV
	};

	return bufferData;
}

void Sprite::CheckCollisionWithTilemap()
{
	// Acá llamar a una función del Tilemap que reciba la posición actual del Sprite.
	// Y que esa función del Tilemap devuelva un array de vec3 con todos los tiles 
	// con los que pueda colisionar. (o... que solo me devuelva los que están a la
	// derecha e izquierda ¬¬).

	glm::vec3 posOfTile;

	if (tilemap->IsColliding(GetPosition(), posOfTile))
	{

	}

}