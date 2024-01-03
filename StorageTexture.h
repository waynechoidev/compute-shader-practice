#pragma once

#include <GL\glew.h>
#include<stdlib.h>

class StorageTexture
{
public:
	StorageTexture();

	void initialise(GLint width, GLint height);
	void useToCompute();
	void useToDraw();
	void clear();

	~StorageTexture();

private:
	GLuint _textureID;
};