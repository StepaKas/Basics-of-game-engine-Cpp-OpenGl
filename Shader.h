#pragma once
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
#include <string.h> 
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "OpenGLInit.h"
#include <SOIL.h>

using namespace std;

class Object;
class Shader
{
private:
	GLuint shader_program;
public:
	

	const char* vertex_text;
	const char* fragment_text;

	GLint texture(const char * uniform) {

		return glGetUniformLocation(shader_program, uniform);
	
	}
	void cam_pos(float x, float y, float z) {
		glUniform3f(glGetUniformLocation(shader_program, "camPos"), x, y, z);
	}


	void light_pos(float x, float y, float z) {
		glUniform3f(glGetUniformLocation(shader_program, "lightObjectPos"), x, y, z);
	}

	void light_color(float r, float g, float b, float a) {
		glUniform4f(glGetUniformLocation(shader_program, "col"), r, g, b, a);
	}
	void light_pos_multiple(vector<Object*> obs);

	void set_lights_object_color(vector<Object*> obs);

	int  modelloc() {
		return glGetUniformLocation(shader_program, "model");
	}
	void  modellocTangent(glm::mat4& M) {
		GLint idModelTransform = glGetUniformLocation(shader_program, "modelMatrix");
		glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &M[0][0]);
	}
	void uniform_matrix(const char* uniform, glm::mat4 cameraMatrix  )
	{
		glUniformMatrix4fv(glGetUniformLocation(shader_program, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
	}
	void spec_intensity(float inten) {
		glUniform1f(glGetUniformLocation(shader_program, "specular_intensity"), inten);
	}
	void use_shader() {
		glUseProgram(shader_program);
	}

	GLuint get_status() {
		GLint status;
		glGetProgramiv(shader_program, GL_LINK_STATUS, &status);
		return status;
	}

	void shader_ok() {
		GLint infoLogLength;
		glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(shader_program, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	void tangent_staff() {
		GLint idTexUnit = glGetUniformLocation(shader_program, "UIAlbedo");
		glUniform1i(idTexUnit, TEXTURE_ALBEDO_ID);
		idTexUnit = glGetUniformLocation(shader_program, "UINormal");
		glUniform1i(idTexUnit, TEXTURE_NORMAL_MAP_ID);
	}
	void check_errors() {
		GLint status6;
		status6 = this->get_status();
		if (status6 == GL_FALSE)
		{
			this->shader_ok();
		}
	}
	
	Shader() {};
	
	void read_text_from_file(const char* vertexFile, const char* fragmentFile);

	void init_shader() {
		
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		//cout << "Vert: \n\n" << vertex_text << endl;
		glShaderSource(vertexShader, 1, &vertex_text, NULL);
		//cout << "Vert: \n\n" << vertex_text << endl;
		glCompileShader(vertexShader);
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		//cout << "Frag: \n\n" << vertex_text << endl;
		glShaderSource(fragmentShader, 1, &fragment_text, NULL);
		//cout << "Frag: \n\n" << vertex_text << endl;
		glCompileShader(fragmentShader);

		GLuint shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, fragmentShader);
		glAttachShader(shaderProgram, vertexShader);
		glLinkProgram(shaderProgram);
		shader_program = shaderProgram;		
	}

	void init_texture(const char* figure, int texture_position);

	void look_at_direction(float x, float y ,float z) {
		glUniform3f(glGetUniformLocation(shader_program, "lookingDirection"), x, y, z);
	}
	string loadFile(const char* fname);


	void send_texture_id(int pos) {
		GLint uniformID = glGetUniformLocation(shader_program, "textureUnitID");
		glUniform1i(uniformID, pos);
		glUniform1i(glGetUniformLocation(shader_program, "texture_position_index"), pos);
		glUniform1i(glGetUniformLocation(shader_program, "cubemap"), pos);
	}
};

