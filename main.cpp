
#include "RunGame.h"
#include "Camera.h"
#include  <cstdlib>
#include <iomanip>
#include <random>


void add_objects() {


	RunGame::return_instance()->add_skybox("texture", -0, 0, 0, 20.0, 20.0, 20.0);

	// max 3 lights dalsi se ignoruje 
	RunGame::return_instance()->add_sphere_light_source("light_source", 3.0, 1.0, 7.0, 0, 0, 0, 0.2, 0.2, 0.2, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, true);
	RunGame::return_instance()->add_sphere_light_source("light_source", 8.0, 1.0, 7.0, 0, 0, 0, 0.2, 0.2, 0.2, 1.0, 1, 1, 0, 0, 0);
	RunGame::return_instance()->add_sphere_light_source("light_source", -4.0, 1.0, 7.0, 0, 0, 0, 0.2, 0.2, 0.2, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0);


	RunGame::return_instance()->add_cube("default", -2, 0, 0, -1, 0, 0);
	RunGame::return_instance()->add_cube("default", 2, 0, 0, 1, 0, 0);
	RunGame::return_instance()->add_cube("default", 0, 0, -2, 0, 0, 0);
	RunGame::return_instance()->add_cube("default", 0, 2, 0, 1, 1, 1);
	RunGame::return_instance()->add_pyramid("default", 0, -5, 0, 0, 0, 0);

	RunGame::return_instance()->add_suzy_smooth("phong", 2, 0, 2, 0, 0, 0, 1, 1, 1);
//	RunGame::return_instance()->add_suzy_flat("phong", 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0);
	RunGame::return_instance()->add_suzy_flat("phong", 4, 2, 2, 0, 0, 0, 1, 1, 1, 0, 1, 0);
	RunGame::return_instance()->add_sphere("phong", 2, 2, 2, 0, 0, 0, 1, 1, 1);

	RunGame::return_instance()->add_sphere("phong", 6.0, 1.0, 7.0, 0, 0, 0, 1, 1, 1);
	RunGame::return_instance()->add_sphere("phong", 0.0, 1.0, 7.0, 0, 0, 0, 1, 1, 1);
	RunGame::return_instance()->add_sphere("phong", 3.0, 1.0, 10.0, 0, 0, 0, 1, 1, 1);
	RunGame::return_instance()->add_sphere("phong", 3.0, 1.0, 4.0, 0, 0, 0, 1, 1, 1);






	//RunGame::return_instance()->add_texture_plain("texture", 10.0, -4.0, 14.0, 40.0, 1.0, 40.0);

	RunGame::return_instance()->add_building("texture", -30.0, -4.0, 14.0, 5.0, 5.0, 5.0);
//	RunGame::return_instance()->add_skydome("texture", -10.0, -4.0, 14.0, 10.0, 10.0, 10.0);

	RunGame::return_instance()->add_zombie("texture", -0, 5,0.0, 20.0, 20.0, 20.0, true, 
		glm::mat4(
			glm::vec4(-1.0, 3.0, -3.0, 1.0),
			glm::vec4(3.0, -6.0, 3.0, 0),
			glm::vec4(-3.0, 3.0, 0, 0),
			glm::vec4(1, 0, 0, 0))
		 , 
		glm::mat4x3(
			glm::vec3(0, 0 ,0),
			glm::vec3(2, 0, 1),
			glm::vec3(4, 0, -1),
			glm::vec3(6, 0,0))
	);

	RunGame::return_instance()->add_zombie("texture", -10, 5, 0.0, 20.0, 20.0, 20.0, true,
		glm::mat4(
			glm::vec4(-1.0, 3.0, -3.0, 1.0),
			glm::vec4(3.0, -6.0, 3.0, 0),
			glm::vec4(-3.0, 3.0, 0, 0),
			glm::vec4(1, 0, 0, 0))
		,
		glm::mat4x3(
			glm::vec3(0, 0, 0),
			glm::vec3(2, 0, 2),
			glm::vec3(4, 0, 4),
			glm::vec3(6, 0, 0))
	);

	RunGame::return_instance()->add_zombie("texture", 10, 5, 0.0, 1.0, 1.0, 1.0);

	RunGame::return_instance()->add_zombie("texture", 0, 5, 10, 1.0, 1.0, 1.0);

	RunGame::return_instance()->add_tree_from_file("texture", 10, 0, 10, 1, 1, 1);

	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			int randNum = rand() % 10;
			RunGame::return_instance()->add_zombie("texture", (rand() % 100)+100, 0, (rand() % 100) + 100, randNum, randNum, randNum, true,
				glm::mat4(
					glm::vec4(-1.0, 3.0, -3.0, 1.0),
					glm::vec4(3.0, -6.0, 3.0, 0),
					glm::vec4(-3.0, 3.0, 0, 0),
					glm::vec4(1, 0, 0, 0))
				,
				glm::mat4x3(
					glm::vec3(0, 0, 0),
					glm::vec3((rand() % 10)- 5 , 0, (rand() % 6) - 3),
					glm::vec3((rand() % 10) - 5, 0, (rand() % 10) - 5),
					glm::vec3(0, 0, (rand() % 10) - 5))
			);
		}
	}
	

	//RunGame::return_instance()->add_ball_with_normal_map("tangent", 0, 0, 0, 1.0, 1.0, 1.0);

	//RunGame::return_instance()->add_teren_with_grass("texture", 10, -4, 1, 5.0, 1.0, 5.0);
	RunGame::return_instance()->add_teren_from_blender("texture", 10, -4, 1, 20.0, 20.0, 20.0);
	RunGame::return_instance()->add_wall("texture", 0, -4, -60, 5.0, 5.0, 5.0);
	RunGame::return_instance()->add_wall("texture", 50, -4, -60, 5.0, 5.0, 5.0);
	RunGame::return_instance()->add_wall("texture", 0, -4, 80, 5.0, 5.0, 5.0);	
	RunGame::return_instance()->add_wall("texture", 50, -4, 80, 5.0, 5.0, 5.0);

	RunGame::return_instance()->add_wall("texture", 100, -4, -30, 0.4, 5.0, 50.0);
	RunGame::return_instance()->add_wall("texture", 100, -4, 50, 0.1, 5.0, 50.0);

	RunGame::return_instance()->add_cube_from_blender("texture", 30, 0, 0, 1, 1, 1);

	RunGame::return_instance()->add_woodbox_from_blender("texture", 26, 10, 0, 1, 1, 1);
	RunGame::return_instance()->add_woodbox_from_blender("texture", 38, 10, 0, 1, 1, 1);
	RunGame::return_instance()->add_woodbox_from_blender("texture", 34, 10, 0, 1, 1, 1);
	RunGame::return_instance()->add_woodbox_from_blender("texture", 30, 10, 0, 1, 1, 1);

	RunGame::return_instance()->add_chair_from_blender("texture", 45, 10, 0, 1, 1, 1);
	RunGame::return_instance()->add_anime_from_blender("texture", 40, 25, 1, 10, 10, 10);

	//RunGame::return_instance()->add_plain_shadow_from_blender("texture", 40, 10, 0, 0.01, 0.01, 0.01);
	//RunGame::return_instance()->add_cube_shadow_from_blender("texture", 40, 10, 0, 0.01, 0.01, 0.01);
	//RunGame::return_instance()->add_table_shadow_from_blender("texture", 40, 10, 0, 0.01, 0.01, 0.01);


	RunGame::return_instance()->add_tower_baked_shadow("texture", 40, 10, 0, 1, 1, 1);

	
}
int main(void)
{

	
	add_objects();
	RunGame::return_instance()->init_all();
	RunGame::return_instance()->run();
	
}

