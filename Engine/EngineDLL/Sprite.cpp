#include "Sprite.h"

Sprite::Sprite(
	Renderer* renderer,			 // Renderer reference
	Material* material,			 // Material reference
	Layers layer,				 // Layer of the Entity
	const char* imagePath,		 // Path of the image
	bool isAnimated,			 // IsAnimated? Yes/No
	const unsigned int sColumns, // Columns of the spritesheet
	const unsigned int sRows, 	 // Rows of the spritesheet
	const float colliderWidth, 	 // Width of the collider
	const float colliderHeight	 // Height of the collider
)
	: Shape(renderer, material, layer), actualFrame(0), columns(sColumns), rows(sRows),
	  isAnimated(isAnimated),
	  widthOfFrame ((int)(header.width  / sColumns)),
	  heightOfFrame((int)(header.height / sRows))
{
	header = TextureImporter::loadBMP_custom(imagePath);

	textureId = renderer->GenTexture(header.width, header.height, header.data);

	count = 4;
	variables = 3;

	verticesData = new float[count * 3]{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
	};

	/*verticesTextureData = new float[count * 2]{
		2/4, 1.0f - 2/4,
		3/4, 1.0f - 2/4,
		2/4, 1.0f - 1/4,
		3/4, 1.0f - 1/4,
	};*/

	verticesTextureData = new float[count * 2]{
		0.0f, 1.0f - 1.0f,
		1.0f, 1.0f - 1.0f,
		0.0f, 1.0f - 0.0f,
		1.0f, 1.0f - 0.0f,
	};

	drawMode = GL_TRIANGLE_STRIP;

	bufferId = SetVertices(verticesData, count);
	textureId = SetTextureUV(verticesTextureData, count, 2);

	unsigned int frames[5] = { 0, 1, 2, 3, 4 };
	if (isAnimated) anim = new Animation(this, frames, false, 24.0f);

	col.x = colliderWidth;
	col.y = colliderHeight;
}

Sprite::~Sprite()
{
	delete verticesData;
	delete verticesTextureData;
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
	renderer->BindTextureBuffer(textureId, 1);
	renderer->DrawBuffer(0, count, drawMode);
	renderer->DisableAttributes(0);
	renderer->DisableAttributes(1);
}

unsigned int Sprite::SetTextureUV(float* vertices, int count, int variables)
{
	//verticesData = vertices;

	unsigned int id = renderer->GenBuffer(vertices, sizeof(float) * count * variables);
	shouldDispose = true;

	return id;
}

void Sprite::SetNextFrame(unsigned int newFrame)
{
	actualFrame = newFrame;

	int uvBufferSize = sizeof(float) * count * 2;
	unsigned int u = (actualFrame % columns) * widthOfFrame;
	unsigned int v = (int)(actualFrame / rows) * heightOfFrame;

	//uvBufferData = setVerticesUV(u, v);
	//uvBufferID = renderer->generateVertexBuffer(_uvBufferData, uvBufferSize);
}