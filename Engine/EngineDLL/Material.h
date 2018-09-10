#pragma once

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include "Exports.h"
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "glm/glm.hpp"

using namespace glm;

class ENGINEDLL_API Material
{
public:
	unsigned int LoadShader(const char * vertex_file_path, const char * fragment_file_path);
	
	void Bind(unsigned int programId);

	Material();
	~Material();
};

