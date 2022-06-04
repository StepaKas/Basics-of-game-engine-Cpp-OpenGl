#pragma once
#include "shader.h"
#include "Camera.h"
#include "OpenGLInit.h"

struct Vertex
{
	float Position[3];
	float Normal[3];
	float Texture[2];
	float Tangent[3];
};


class VAO {
public:
	GLuint ID = 0;
	int size_of_coords;
	int size_of_color;


	virtual void init_VAO(GLuint& VBO) {


		

		
		glGenVertexArrays(1, &ID); //generate the VAO

		glBindVertexArray(ID); //bind the VAO

		glEnableVertexAttribArray(0); //enable vertex attributes

		glEnableVertexAttribArray(1);
		//if (size_of_textures != 0)
		//{
		//	glEnableVertexAttribArray(2);
		//}
		


		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glVertexAttribPointer(0, size_of_coords, GL_FLOAT, GL_FALSE, (size_of_coords + size_of_color) * sizeof(float), (GLvoid*)0);
		// Barva nebo normála
		glVertexAttribPointer(1, size_of_color, GL_FLOAT, GL_FALSE, (size_of_coords + size_of_color ) * sizeof(float), (GLvoid*)(size_of_coords * sizeof(GL_FLOAT)));
		//if (size_of_textures != 0)
		//{
		//	glVertexAttribPointer(2, size_of_textures, GL_FLOAT, GL_FALSE, (size_of_coords + size_of_color + size_of_textures) * sizeof(float), (GLvoid*)((size_of_coords + size_of_color) * sizeof(GL_FLOAT)));
		//}

		

		

		
	}

	VAO( int size_of_coords, int size_of_color) : size_of_coords(size_of_coords) , size_of_color(size_of_color){

	}
	VAO(){}
};