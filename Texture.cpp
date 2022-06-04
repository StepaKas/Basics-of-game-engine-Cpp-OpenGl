#include"Texture.h"

Texture::Texture(const char* pic_file, int text_pos_p) : file_path(pic_file), text_pos(text_pos_p)
{
	glActiveTexture(GL_TEXTURE0 + text_pos_p);
	GLuint textureID = SOIL_load_OGL_texture(pic_file, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (textureID == NULL) {
		std::cout << "An error occurred while loading image." << std::endl;
		exit(EXIT_FAILURE);
	}
	printf("Figure %s was set as a texture succesfully\n", pic_file);
	glBindTexture(GL_TEXTURE_2D, textureID);
	ID = textureID;
}

Texture::Texture(const char* pic_file, int text_pos_p, const char* neco) : file_path(pic_file), text_pos(text_pos_p)
{
	glActiveTexture(GL_TEXTURE0 + text_pos_p);
	GLuint textureID = SOIL_load_OGL_texture(pic_file, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (textureID == NULL) {
		std::cout << "An error occurred while loading image." << std::endl;
		exit(EXIT_FAILURE);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
		GL_REPEAT); // opakovani textury
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
		GL_REPEAT);
	printf("Figure %s was set as a texture succesfully\n", pic_file);
	glBindTexture(GL_TEXTURE_2D, textureID);
	ID = textureID;
}

Texture::Texture(int text_pos_p)
{
	glActiveTexture(GL_TEXTURE0 + text_pos_p);
	GLuint textureID = SOIL_load_OGL_cubemap("models/posx.jpg", "models/negx.jpg", "models/posy.jpg", "models/negy.jpg", "models/posz.jpg", "models/negz.jpg", SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	if (textureID == NULL) {
		std::cout << "An error occurred while loading image." << std::endl;
		exit(EXIT_FAILURE);
	}
	printf("Figure %s was set as a texture succesfully\n", "skybox");
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	ID = textureID;

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

}

