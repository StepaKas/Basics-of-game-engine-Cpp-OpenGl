#pragma once
#include "Texture.h"

class RunGame {
private:
	

	std::vector <Object*> objecty_default_shader;
	std::vector <Object*> objecty_lambert_shader;
	std::vector <Object*> objecty_phong_shader;
	std::vector <Object*> objecty_blinn_shader;
	std::vector <Object*> objecty_light_source_shader;
	std::vector <Object*> objecty_tangent_shader;



	Shader* shader;
	Shader* lambert_shader;
	Shader* phong_shader;
	Shader* blinn_shader;
	Shader* light_source_shader;
	Shader* tangent_shader;



	// makes this class singleton
	float rotation = 0.0f;
	double prevTime = glfwGetTime();
	glm::mat4 M = glm::mat4(1.0f);
	GLFWwindow* window;

	void choose_shader(const char* shader, Object* O);
	RunGame();

	static RunGame* hra;
public:
	Shader* texture_shader;
	std::vector <Object*> objecty_texture_shader;
	static RunGame* return_instance();

	RunGame(Shader* _shader);
	~RunGame();


	void run();
	
	void init_all();

	void add_cube(const char* shader, float x  , float y , float z , float rot_x , float rot_y, float rot_z);
	void add_pyramid(const char* shader, float x, float y, float z, float rot_x, float rot_y, float rot_z);
	void add_suzy_flat(const char* shader, float x, float y, float z, float rot_x, float rot_y, float rot_z, float scale_x, float scale_y, float scale_z, float static_rot_x, float static_rot_y, float static_rot_z);
	void add_suzy_smooth(const char* shader, float x, float y, float z, float rot_x, float rot_y, float rot_z, float scale_x, float scale_y, float scale_z);
	void add_sphere(const char* shader, float x, float y, float z, float rot_x, float rot_y, float rot_z, float scale_x, float scale_y, float scale_z);
	void add_sphere_light_source(const char* shader, float x, float y, float z, float rot_x, float rot_y, float rot_z, float scale_x, float scale_y, float scale_z, float diffuse_r, float diffuse_g, float diffuse_b, float specular_r, float specular_g, float specular_b, bool is_bezier = false,

		glm::mat4 A =
		glm::mat4(
			glm::vec4(-1.0, 3.0, -3.0, 1.0),
			glm::vec4(3.0, -6.0, 3.0, 0),
			glm::vec4(-3.0, 3.0, 0, 0),
			glm::vec4(1, 0, 0, 0)
		),
		glm::mat4x3 B =
		glm::mat4x3(
			glm::vec3(0, 0, 0),
			glm::vec3(2, 2, 0),
			glm::vec3(4, 4, 0),
			glm::vec3(6, 0, 0)
		)

	);

	void add_tree(const char* shader, float x, float y, float z, float rot_x, float rot_y, float rot_z, float scale_x, float scale_y, float scale_z, float static_rot_x, float static_rot_y, float static_rot_z);
	void add_plain(const char* shader, float x, float y, float z);
	void add_gift(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z);
	void add_bush(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z);
	void add_texture_plain(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z);
	void add_building(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z);
	void add_skydome(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z);

	void add_zombie(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z, bool is_bezier= false ,
		
		glm::mat4 A = 
			glm::mat4(
				glm::vec4(-1.0, 3.0, -3.0, 1.0),
				glm::vec4(3.0, -6.0, 3.0, 0),
				glm::vec4(-3.0, 3.0, 0, 0),
				glm::vec4(1, 0, 0, 0)
			),
		glm::mat4x3 B = 
			glm::mat4x3(
				glm::vec3(0, 0, 0),
				glm::vec3(2, 2, 0),
				glm::vec3(4, 4, 0),
				glm::vec3(6, 0, 0)
			)
	
	);

	void add_plain_from_file(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z);
	void add_tree_from_file(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z);
	void add_skybox(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z);
	void add_teren_with_grass(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z);
	void add_ball_with_normal_map(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z);
	void add_wall(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z);
	void add_cube_from_blender(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z);

	void add_texture_object(const char* path, float x, float y, float z, float scale_x, float scale_y, float scale_z);
	void add_woodbox_from_blender(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z);
	void add_chair_from_blender(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z);
	void add_teren_from_blender(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z);
	void add_lady_cat_from_blender (const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z);

	void add_anime_from_blender(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z);

	void add_cube_shadow_from_blender(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z);
	void add_table_shadow_from_blender(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z);
	void add_plain_shadow_from_blender(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z);

	void add_tower_baked_shadow(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z);
};

