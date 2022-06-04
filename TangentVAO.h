#pragma once
#include "TextureVAO.h"
class TangentVAO : public TextureVAO
{
protected: 
	int size_of_tangent;
public:

	TangentVAO(int coord, int normal, int textures, int tangents) {
		//	cout << coord << " " << normal << " " << textures << endl;
		size_of_color = normal;
		size_of_coords = coord;
		size_of_textures = textures;
		size_of_tangent = tangents;
	}
	virtual void init_VAO(GLuint& VBO) {

		//cout << "init texVAO " << size_of_coords << " " << size_of_color << " " << size_of_textures << endl;
		glGenVertexArrays(1, &ID); //generate the VAO

		glBindVertexArray(ID); //bind the VAO

		glEnableVertexAttribArray(0); //enable vertex attributes

		glEnableVertexAttribArray(1);

		glEnableVertexAttribArray(2);

		glEnableVertexAttribArray(3);


		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		int offset = size_of_coords + size_of_color + size_of_textures + size_of_tangent;
		glVertexAttribPointer(0, size_of_coords, GL_FLOAT, GL_FALSE, offset * sizeof(float), (GLvoid*)0);
		// Barva nebo normála
		glVertexAttribPointer(1, size_of_color, GL_FLOAT, GL_FALSE, offset * sizeof(float), (GLvoid*)(size_of_coords * sizeof(GL_FLOAT)));


		glVertexAttribPointer(2, size_of_textures, GL_FLOAT, GL_FALSE, offset * sizeof(float), (GLvoid*)((size_of_coords + size_of_color) * sizeof(GL_FLOAT)));

		glVertexAttribPointer(3, size_of_tangent, GL_FLOAT, GL_FALSE, offset * sizeof(float), (GLvoid*)((size_of_coords + size_of_color + +size_of_tangent) * sizeof(GL_FLOAT)));

	}
};

