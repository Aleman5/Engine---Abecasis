#include "TextureImporter.h"

TextureImporter::TextureImporter()
{
}
TextureImporter::~TextureImporter()
{
}

unsigned int TextureImporter::loadBMP_custom(const char* imagePath)
{
	unsigned int textureId;

	// Lectura de información del encabezado del archivo
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width * height * 3
							  // Information RGB
	unsigned char * data;

	FILE * file = fopen(imagePath, "rb");
	if (!file) { printf("Image could not be opened\n"); return 0; }

	if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
		return false;
	}

	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
		return 0;
	}

	// Lectura de los enteros desde el arreglo de bytes
	dataPos   = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width	  = *(int*)&(header[0x12]);
	height	  = *(int*)&(header[0x16]);

	// Algunos archivos BMP tienen un mal formato, así que adivinamos la información faltante
	if (imageSize == 0)    imageSize = width * height * 3; // 3 : un byte por cada componente Rojo (Red), Verde (Green) y Azul(Blue)
	if (dataPos == 0)      dataPos = 54; // El encabezado del BMP está hecho de ésta manera

	// Se crea un buffer
	data = new unsigned char[imageSize];

	// Leemos la información del archivo y la ponemos en el buffer
	fread(data, 1, imageSize, file);

	//Todo está en memoria ahora, así que podemos cerrar el archivo
	fclose(file);

	return textureId;
}