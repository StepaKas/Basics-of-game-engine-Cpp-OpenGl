#pragma once


#include "TextureObject.h"

class Texture
{
public:
	GLuint ID;
	const char* file_path;
	int text_pos;
	Texture(const char * pic_file, int text_pos_p);
	//TEREN
	Texture(const char* pic_file, int text_pos_p, const char * neco);
	//skybox
	Texture( int text_pos_p);

};
