#pragma once
#include "VAO.h"
class TextureVAO :
    public VAO
{
protected:

	int size_of_textures = 0;
public:
	TextureVAO() {

	}
    TextureVAO(int coord, int normal, int textures) {
	//	cout << coord << " " << normal << " " << textures << endl;
		size_of_color = normal;
		size_of_coords = coord;
		size_of_textures = textures;
    }
    virtual void init_VAO(GLuint& VBO) {

		//cout << "init texVAO " << size_of_coords << " " << size_of_color << " " << size_of_textures << endl;
		glGenVertexArrays(1, &ID); //generate the VAO

		glBindVertexArray(ID); //bind the VAO

		glEnableVertexAttribArray(0); //enable vertex attributes

		glEnableVertexAttribArray(1);

		glEnableVertexAttribArray(2);
		



		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glVertexAttribPointer(0, size_of_coords, GL_FLOAT, GL_FALSE, (size_of_coords + size_of_color + size_of_textures) * sizeof(float), (GLvoid*)0);
		// Barva nebo normála
		glVertexAttribPointer(1, size_of_color, GL_FLOAT, GL_FALSE, (size_of_coords + size_of_color + size_of_textures) * sizeof(float), (GLvoid*)(size_of_coords * sizeof(GL_FLOAT)));

		
		glVertexAttribPointer(2, size_of_textures, GL_FLOAT, GL_FALSE, (size_of_coords + size_of_color + size_of_textures) * sizeof(float), (GLvoid*)((size_of_coords + size_of_color) * sizeof(GL_FLOAT)));
		

    }

};

