#include "shader.h"
#include "Camera.h"
#include "LightSource.h"


std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}


void Shader::light_pos_multiple(vector<Object*> obs)
{
	//objecty_light_source_shader[0]->modely[0]->x;
	// mam tri svetla
	for (size_t i = 0; i < obs.size(); i++)
	{
		int x = obs[i]->modely[0]->x_m;
		int y = obs[i]->modely[0]->y_m;
		int z = obs[i]->modely[0]->z_m;

		int diffuse_r = ((LightSource*)obs[i])->diffuse_r;
		int diffuse_g = ((LightSource*)obs[i])->diffuse_g;
		int diffuse_b = ((LightSource*)obs[i])->diffuse_b;
		int diffuse_a = ((LightSource*)obs[i])->diffuse_a;


		int specular_r = ((LightSource*)obs[i])->specular_r;
		int specular_g = ((LightSource*)obs[i])->specular_g;
		int specular_b = ((LightSource*)obs[i])->specular_b;
		int specular_a = ((LightSource*)obs[i])->specular_a;


		string index_pos;
		//"lights[i].position"
		index_pos.append("lights[");
		index_pos.append(std::to_string(i));
		index_pos.append("].position");

		string index_diffuse;
		index_diffuse.append("lights[");
		index_diffuse.append(std::to_string(i));
		index_diffuse.append("].diffuse");


		string index_specular;
		index_specular.append("lights[");
		index_specular.append(std::to_string(i));
		index_specular.append("].specular");


 		glUniform3f(glGetUniformLocation(shader_program, index_pos.c_str()), x, y, z);
		glUniform4f(glGetUniformLocation(shader_program, index_diffuse.c_str()), diffuse_r, diffuse_g, diffuse_b, diffuse_a);
		glUniform4f(glGetUniformLocation(shader_program, index_specular.c_str()), specular_r, specular_g, specular_b, specular_a);
	}

}

void Shader::set_lights_object_color(vector<Object*> obs)
{
	for (size_t i = 0; i < obs.size(); i++)
	{


		int diffuse_r = ((LightSource*)obs[i])->diffuse_r;
		int diffuse_g = ((LightSource*)obs[i])->diffuse_g;
		int diffuse_b = ((LightSource*)obs[i])->diffuse_b;
		int diffuse_a = ((LightSource*)obs[i])->diffuse_a;

		int specular_r = ((LightSource*)obs[i])->specular_r;
		int specular_g = ((LightSource*)obs[i])->specular_g;
		int specular_b = ((LightSource*)obs[i])->specular_b;
		int specular_a = ((LightSource*)obs[i])->specular_a;

		string index_diffuse;
		index_diffuse.append("lights[");
		index_diffuse.append(std::to_string(i));
		index_diffuse.append("].diffuse");

		string index_specular;
		index_specular.append("lights[");
		index_specular.append(std::to_string(i));
		index_specular.append("].specular");

		glUniform4f(glGetUniformLocation(shader_program, index_diffuse.c_str()), diffuse_r, diffuse_g, diffuse_b, diffuse_a);
		glUniform4f(glGetUniformLocation(shader_program, index_specular.c_str()), specular_r, specular_g, specular_b, specular_a);
	}
}

void Shader::read_text_from_file(const char* vertexFile, const char* fragmentFile)
{
	printf("Shader::loadShader %s %s \n", vertexFile, fragmentFile);
	string vertexShaderString = loadFile(vertexFile);
	string fragmentShaderString = loadFile(fragmentFile);

	if (vertexShaderString.empty()) printf("Empty Vertex Shader\n");
	if (fragmentShaderString.empty()) printf("Empty Fragment Shader\n");

	vertex_text = vertexShaderString.c_str();
	fragment_text = fragmentShaderString.c_str();
	
	//cout <<"Fragment " << strcmp(default_frag1, fragment_text) << " Vertex: " << strcmp(default_vertex1, vertex_text) << endl;

	//cout << default_vertex1 << "\n" << default_frag1 << endl;
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

void Shader::init_texture(const char* figure, int texture_position)
{
	glActiveTexture(GL_TEXTURE0 + texture_position);
	GLuint textureID = SOIL_load_OGL_texture(figure, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	glBindTexture(GL_TEXTURE_2D, textureID);
	


	//Set texture unit to fragment shader
	GLint uniformID = glGetUniformLocation(shader_program, "textureUnitID");
	glUniform1i(uniformID, texture_position);


}


string Shader::loadFile(const char* fname)
{
	ifstream file(fname);
	if (!file.is_open())
	{
		cout << "Unable to open file " << fname << endl;
		//exit(1);
	}
	std::stringstream fileData;
	fileData << file.rdbuf();
	file.close();
	return fileData.str();
}
