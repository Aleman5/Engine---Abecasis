#pragma once

#include "Renderer.h"

class ENGINEDLL_API Entity
{
protected:
	GLenum drawMode;
	Renderer* renderer;
	Material* material;
	unsigned int bufferId;
	unsigned int colorBufferId;
	unsigned int programId;
	bool shouldDispose;

	glm::vec3 vectorPosition;	// Actual Position.
	glm::vec3 vectorRotation;	// Actual Rotation.
	glm::vec3 vectorScale;		// Actual Scale.

	glm::mat4 model;			// Model Matrix.

	glm::mat4 translationMatrix;// Translation Matrix.
	glm::mat4 rotateX;			// RotationX Matrix.
	glm::mat4 rotateY;			// RotationX Matrix.
	glm::mat4 rotateZ;			// RotationX Matrix.
	glm::mat4 scallingMatrix;	// Scale Matrix.

	float colWidth;
	float colHeight;

public:
	virtual void Draw() = 0;
	virtual void ShouldDispose() = 0;

	void UpdateModel();
	void Translate(
		glm::vec3 vector3	// Vector3 to Translate.
	);
	void Translate(
		float newX,	// Value in X.
		float newY,	// Value in Y.
		float newZ	// Value in Z.
	);
	void Scale(
		glm::vec3 vector3	// Vector3 to Scale.
	);
	void Scale(
		float newX, // Value in X.
		float newY, // Value in Y.
		float newZ  // Value in Z.
	);
	void RotateX(
		float angle // Value in X axis.
	);
	void RotateY(
		float angle // Value in Y axis.
	);
	void RotateZ(
		float angle // Value in Z axis.
	);
	virtual unsigned int SetVertices(
		float* vertices,	// Vertices data.
		int count			// Total of vertices.
	) = 0;

	Entity(Renderer* renderer,	// Renderer reference.
		   Material* material	// Material reference.
	);
	~Entity();
};

