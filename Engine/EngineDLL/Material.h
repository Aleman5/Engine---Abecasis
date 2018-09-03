#pragma once

#include<ios>
#include "Exports.h"
#include "GL\glew.h"

class ENGINEDLL_API Material
{
public:
	unsigned int LoadShader(const char * vertex_file_path, const char * fragment_file_path);

	Material();
	~Material();
};

