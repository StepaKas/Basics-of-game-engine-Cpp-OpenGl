#include "RunGame.h"

#include "suzi_flat.h"
#include "sphere.h"
#include "suzi_smooth.h"
#include "tree.h"
#include "gift.h"
#include "bushes.h"

#include "texture_plain.h"
#include "skybox.h"
#include "shaders_text.h"
#include "building.h"
#include "skydome.h"
RunGame* RunGame::hra = 0;


RunGame::RunGame() {

}

RunGame* RunGame::return_instance()
{
	if (hra == NULL)
	{
		hra = new RunGame;
	}

	return RunGame::hra;
}

RunGame::RunGame(Shader* _shader) :shader(_shader) {

}

RunGame::~RunGame() {
	hra = 0;
}

void resize(GLFWwindow * win , int w ,int h) {
	glViewport(0, 0, w, h);
	Camera::return_instance()->change_width_height(w, h);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Camera::return_instance()->Inputs(window);

}

void cursor_callback(GLFWwindow* window, double x, double y) { 
	Camera::return_instance()->Inputs(window);

}

void button_callback(GLFWwindow* window, int button, int action, int mode) {
	Camera::return_instance()->Inputs(window);
	//if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}
void RunGame::run()
{
	

	//Texture textura(("pics/test.png"), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	//textura.texUnit(texture_shader, "tex0", 0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowSizeCallback(window, resize);
	glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetMouseButtonCallback(window, button_callback);


	while (!glfwWindowShouldClose(window)) {

		// RESIZE OKNA
		
		//if (width_new != width || height_new != height)
		//{

		//	Camera::return_instance()->change_width_height(width_new, height_new);
		//	glViewport(0, 0, width_new, height_new);
		//	width = width_new;
		//	height = height_new;

		//}
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		
		Camera::return_instance()->updateMatrix(45.0f, 0.1f, 500.0f);


		for (size_t i = 0; i < objecty_texture_shader.size(); i++) {
			glStencilFunc(GL_ALWAYS, objecty_texture_shader[i]->id, 0xFF);
			if (objecty_texture_shader[i]->id >= 0) {
				(objecty_texture_shader[i])->run_in_the_loop();
			}


		}
		auto campos_x = Camera::return_instance()->Position.x;
		auto campos_y = Camera::return_instance()->Position.y;
		auto campos_z = Camera::return_instance()->Position.z;
		texture_shader->cam_pos(campos_x, campos_y, campos_z);
		texture_shader->light_pos_multiple(objecty_light_source_shader);
		texture_shader->look_at_direction(Camera::return_instance()->Orientation[0], Camera::return_instance()->Orientation[1], Camera::return_instance()->Orientation[2]);
		Camera::return_instance()->Matrix(texture_shader, "camMatrix");

		//defaut shader
		for (size_t i = 0; i < objecty_default_shader.size(); i++){
			objecty_default_shader[i]->run_in_the_loop();
		}
		Camera::return_instance()->Matrix(shader, "camMatrix");
		
		//lamber shader
		

		lambert_shader->cam_pos(campos_x, campos_y, campos_z);

		
		phong_shader->light_pos_multiple(objecty_light_source_shader);
		for (size_t i = 0; i < objecty_lambert_shader.size(); i++) {
			objecty_lambert_shader[i]->run_in_the_loop();
		}		
		Camera::return_instance()->Matrix(lambert_shader, "camMatrix");

		//phong shader
		phong_shader->cam_pos(campos_x, campos_y, campos_z);
		phong_shader->light_pos_multiple(objecty_light_source_shader);

		for (size_t i = 0; i < objecty_phong_shader.size(); i++) {
			objecty_phong_shader[i]->run_in_the_loop();
		}
		Camera::return_instance()->Matrix(phong_shader, "camMatrix");

		blinn_shader->cam_pos(campos_x, campos_y, campos_z);
		blinn_shader->light_pos_multiple(objecty_light_source_shader);
		for (size_t i = 0; i < objecty_blinn_shader.size(); i++) {
			objecty_blinn_shader[i]->run_in_the_loop();
		}
		Camera::return_instance()->Matrix(blinn_shader, "camMatrix");


		//light source shader
		for (size_t i = 0; i < objecty_light_source_shader.size(); i++) {
			( objecty_light_source_shader[i])->run_in_the_loop();
		}
		Camera::return_instance()->Matrix(light_source_shader, "camMatrix");


		
		for (size_t i = 0; i < objecty_tangent_shader.size(); i++) {
			(objecty_tangent_shader[i])->run_in_the_loop();
		}
		tangent_shader->tangent_staff();
		Camera::return_instance()->Matrix(tangent_shader, "modelMatrix");

	//	texture_shader->use_shader();

		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(window);




	}
	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}



void RunGame::init_all()
{	


	window = OpenGLInit::init_all();

	Camera::init_instance(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0f, 20.0f, 20.0f));

	//INIT TEXTURES
	Texture* t1 = new Texture("pics/test.png", TEXTURE_WOOD_ID);
	Texture* t2 = new Texture("pics/building.png", TEXTURE_BUILDING_ID);
	Texture* t3 = new Texture("pics/skydome.png", TEXTURE_SKYDOME_ID);
	Texture* t4 = new Texture("models/zombie.png", TEXTURE_ZOMBIE_ID);
	Texture* t5 = new Texture("models/tree.png", TEXTURE_TREE_ID);
	Texture* t6 = new Texture(TEXTURE_SKYBOX_ID);
	Texture* t7 = new Texture("models/teren/grass.png", TEXTURE_TEREN_GRASS_ID, "");
	Texture* t8 = new Texture("albedo.png", TEXTURE_ALBEDO_ID);
	Texture* t9 = new Texture("normalmap.png", TEXTURE_NORMAL_MAP_ID);
	Texture* t10 = new Texture("models/zed/bake.png", TEXTURE_WALL_ID);//
	Texture* t11 = new Texture("models/CubeTripleTexture.png", TEXTURE_BLEND_CUBE);
	Texture* t12 = new Texture("models/WoodBox.png", TEXTURE_BLEND_WOOD_BOX);
	Texture* t13 = new Texture("models/BakeChair.png", TEXTURE_BLEND_CHAIR);
	Texture* t14 = new Texture("models/Teren.png", TEXTURE_BLEND_TEREN);
	Texture* t15 = new Texture("models/LadyCat.bmp", TEXTURE_BLEND_LADYCAT);
	Texture* t16 = new Texture("models/anime.png", TEXTURE_BLEND_ANIME);
	Texture* t17 = new Texture("models/Stiny/CubeShadow.png", TEXTURE_BLEND_SHADOWCUBE);
	Texture* t18 = new Texture("models/Stiny/PlainShadow.png", TEXTURE_BLEND_SHADOWPLAIN);
	Texture* t19 = new Texture("models/Stiny/TableShadow.png", TEXTURE_BLEND_SHADOWTABLE);
	Texture* t20 = new Texture("models/BlenderFinal/BakedShadowTower.png", TEXTURE_BLEND_SHADOWTABLE);
	//
	//TEXTURE_NORMAL_MAP_ID
	// Defaultní shader
	shader = new Shader;
	shader->read_text_from_file("Constant.vertex", "Constant.fragment");
	
	for (size_t i = 0; i < objecty_default_shader.size(); i++)
	{
		objecty_default_shader[i]->init_models(this->shader);
	}
	

	texture_shader = new Shader;
	texture_shader->read_text_from_file("Texture.vertex", "Texture.fragment");
	for (size_t i = 0; i < objecty_texture_shader.size(); i++)
	{
		objecty_texture_shader[i]->init_models(this->texture_shader);
	}
	//texture_shader->init_texture("pics/test.png", 0);



	//Lambert
	lambert_shader = new Shader;
	lambert_shader->read_text_from_file("Lambert.vertex", "Lambert.fragment");
	
	for (size_t i = 0; i < objecty_lambert_shader.size(); i++)
	{
		objecty_lambert_shader[i]->init_models(lambert_shader);
	}


	//phong
	phong_shader = new Shader;
	phong_shader->read_text_from_file("Phong.vertex","Phong.fragment");
	
	for (size_t i = 0; i < objecty_phong_shader.size(); i++)
	{
		objecty_phong_shader[i]->init_models(phong_shader);
	}


	light_source_shader = new Shader;
	light_source_shader->read_text_from_file("LightSource.vertex", "LightSource.fragment");
	for (size_t i = 0; i < objecty_light_source_shader.size(); i++)
	{
		
		((LightSource*)objecty_light_source_shader[i])->init_models(light_source_shader);
	}


	blinn_shader = new Shader;
	blinn_shader->read_text_from_file("Blinn.vertex", "Blinn.fragment");

	for (size_t i = 0; i < objecty_blinn_shader.size(); i++)
	{
		objecty_blinn_shader[i]->init_models(blinn_shader);
	}

	tangent_shader = new Shader;
	tangent_shader->read_text_from_file("PhongVertexShader.glsl", "PhongFragmentShader.glsl");
	for (size_t i = 0; i < objecty_tangent_shader.size(); i++)
	{
		objecty_tangent_shader[i]->init_models(tangent_shader);
	}


	shader->check_errors();
	lambert_shader->check_errors();
	phong_shader->check_errors();
	light_source_shader->check_errors();
	blinn_shader->check_errors();
	texture_shader->check_errors();
	tangent_shader->check_errors();


}

void RunGame::choose_shader(const char* shader, Object* object)
{
	
	if (strcmp(shader, "default") == 0) {
		this->objecty_default_shader.push_back(object);
	}
	else if (strcmp(shader, "lambert") == 0)
	{
		this->objecty_lambert_shader.push_back(object);
	}
	else if (strcmp(shader, "phong") == 0) {
		this->objecty_phong_shader.push_back(object);
	}
	else if (strcmp(shader, "light_source") == 0) {
		this->objecty_light_source_shader.push_back(object);
	}
	else if (strcmp(shader, "blinn") == 0) {
		this->objecty_blinn_shader.push_back(object);
	}
	else if (strcmp(shader, "texture") == 0) {
		this->objecty_texture_shader.push_back(object);
	}
	else if (strcmp(shader, "tangent") == 0) {
		this->objecty_tangent_shader.push_back(object);
	}
	else {
		throw std::invalid_argument("Nonexisting shader.");
	}
}

void RunGame::add_suzy_flat(const char* shader, float x, float y, float z, float rot_x, float rot_y, float rot_z, float scale_x = 1, float scale_y = 1, float scale_z = 1, float static_rot_x = 0, float static_rot_y = 0, float static_rot_z = 0) {
	Model* O1 = new Model(suziFlat, sizeof(suziFlat) / sizeof(suziFlat[0]));
	
	VAO * _vao = new VAO(3, 3);

	O1->set_vao(_vao);
	O1->edges = 2904;
	O1->type = GL_TRIANGLES;

	Object* object = new Object();
	object->add_model(O1, x, y, z, rot_x, rot_y, rot_z, scale_x, scale_y, scale_z,  static_rot_x ,  static_rot_y , static_rot_z );
	choose_shader(shader, object);

}

void RunGame::add_suzy_smooth(const char* shader, float x, float y, float z, float rot_x, float rot_y, float rot_z, float scale_x = 1, float scale_y = 1, float scale_z = 1) {
	Model* O1 = new Model(suziSmooth, sizeof(suziSmooth) / sizeof(suziSmooth[0]));

	VAO* _vao = new VAO(3, 3);

	O1->set_vao(_vao);
	O1->edges = 2904;
	O1->type = GL_TRIANGLES;


	Object* object = new Object();
	object->add_model(O1, x, y, z, rot_x, rot_y, rot_z, scale_x, scale_y, scale_z);


	choose_shader(shader, object);
}

void RunGame::add_pyramid(const char* shader, float x, float y, float z, float rot_x, float rot_y, float rot_z)
{
	float spodek[] = {

	0.5f + x, 1.0f + y, 0.5f + z, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.5f + x, 1.0f + y, -0.5f + z, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	-0.5f + x, 1.0f + y, -0.5f + z, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	-0.5f + x, 1.0f + y, 0.5f + z, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,


	};

	float trojuhelnik_1[] = {
		0.5f + x, 1.0f + y, 0.5f + z, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.5f + x, 1.0f + y, -0.5f + z, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.0f + x, 2.0f + y, 0.0f + z, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f
	};
	float trojuhelnik_2[] = {
		0.5f + x, 1.0f + y, -0.5f + z, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.5f + x, 1.0f + y, -0.5f + z, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.0f + x, 2.0f + y, 0.0f + z, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f
	};

	float trojuhelnik_3[] = {
		-0.5f + x, 1.0f + y, -0.5f + z, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.5f + x, 1.0f + y, 0.5f + z, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.0f + x, 2.0f + y, 0.0f + z, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f
	};

	float trojuhelnik_4[] = {
		0.5f + x, 1.0f + y, 0.5f + z, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.5f + x, 1.0f + y, 0.5f + z, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.0f + x, 2.0f + y, 0.0f + z, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f
	};



	Model* O1 = new Model(spodek, sizeof(spodek) / sizeof(spodek[0]));
	Model* O2 = new Model(trojuhelnik_1, sizeof(trojuhelnik_1) / sizeof(trojuhelnik_1[0]));
	Model* O3 = new Model(trojuhelnik_2, sizeof(trojuhelnik_2) / sizeof(trojuhelnik_2[0]));
	Model* O4 = new Model(trojuhelnik_3, sizeof(trojuhelnik_3) / sizeof(trojuhelnik_3[0]));
	Model* O5 = new Model(trojuhelnik_4, sizeof(trojuhelnik_4) / sizeof(trojuhelnik_4[0]));

	O1->rot_x = rot_x;
	O1->rot_y = rot_y;
	O1->rot_z = rot_z;
	O1->edges = 4;
	O1->type = GL_POLYGON;

	O2->rot_x = rot_x;
	O2->rot_y = rot_y;
	O2->rot_z = rot_z;
	O2->edges = 3;
	O2->type = GL_TRIANGLES;

	O3->rot_x = rot_x;
	O3->rot_y = rot_y;
	O3->rot_z = rot_z;
	O3->edges = 3;
	O3->type = GL_TRIANGLES;

	O4->rot_x = rot_x;
	O4->rot_y = rot_y;
	O4->rot_z = rot_z;
	O4->edges = 3;
	O4->type = GL_TRIANGLES;

	O5->rot_x = rot_x;
	O5->rot_y = rot_y;
	O5->rot_z = rot_z;
	O5->edges = 3;
	O5->type = GL_TRIANGLES;

	VAO * _vao0= new VAO(4, 4);
	VAO* _vao1 = new VAO(4, 4);
	VAO* _vao2 = new VAO(4, 4);
	VAO* _vao3 = new VAO(4, 4);
	VAO* _vao4 = new VAO(4, 4);
	O1->set_vao(_vao0);
	O2->set_vao(_vao1);
	O3->set_vao(_vao2);
	O4->set_vao(_vao3);
	O5->set_vao(_vao4);

	Object* object = new Object();

	object->add_model(O1);
	object->add_model(O2);
	object->add_model(O3);
	object->add_model(O4);
	object->add_model(O5);


	choose_shader(shader, object);
}

void RunGame::add_sphere(const char* shader, float x, float y, float z, float rot_x, float rot_y, float rot_z, float scale_x = 1, float scale_y = 1, float scale_z = 1)
{
	Model* O1 = new Model(sphere, sizeof(sphere) / sizeof(sphere[0]));

	VAO *_vao = new VAO(3, 3);

	O1->set_vao(_vao);
	O1->edges = 2880;
	O1->type = GL_TRIANGLES;

	Object* object = new Object();
	object->add_model(O1 ,x ,y, z , rot_x, rot_y , rot_z, scale_x , scale_y , scale_z);

	
	choose_shader(shader, object);

}

void RunGame::add_sphere_light_source(const char* shader, float x, float y, float z, float rot_x, float rot_y, float rot_z, float scale_x, float scale_y, float scale_z, float diffuse_r, float diffuse_g, float diffuse_b, float specular_r, float specular_g, float specular_b, bool is_moving_bezier, glm::mat4 A, glm::mat4x3 B)
{
	Model* O1 = new Model(sphere, sizeof(sphere) / sizeof(sphere[0]));

	VAO* _vao = new VAO(3,3);

	O1->set_vao(_vao);
	O1->edges = 2880;
	O1->type = GL_TRIANGLES;
	O1->is_moving_using_bezier =is_moving_bezier;
	O1->A = A;
	O1->B = B;


	LightSource* object = new LightSource();
	object->diffuse_r = diffuse_r;
	object->diffuse_g = diffuse_g;
	object->diffuse_b = diffuse_b;

	object->specular_r = specular_r;
	object->specular_g = specular_g;
	object->specular_b = specular_b;

	object->add_model(O1, x, y, z, rot_x, rot_y, rot_z, scale_x, scale_y, scale_z);


	choose_shader(shader, object);
}

void RunGame::add_cube(const char* shader, float x , float y , float z , float rot_x , float rot_y , float rot_z )
{
	float narys[] = {

	0.5f+x, 0.0f+y, 0.5f + z, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	0.5f+x, 0.0f+y, -0.5f + z, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	-0.5f+x, 0.0f+y, -0.5f + z, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	-0.5f+x, 0.0f+y, 0.5f + z, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

	};

	
	float spodek[] = {

		0.5f + x, 1.0f + y, 0.5f + z, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f + x, 1.0f + y, -0.5f + z, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f + x, 1.0f + y, -0.5f + z, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f + x, 1.0f + y, 0.5f + z, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

	};

	float bok1[] = {


		0.5f+x, 1.0f+ y, 0.5f + z, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f+x, 1.0f+ y, -0.5f + z, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f+x, 0.0f+ y, -0.5f + z, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f+x, 0.0f+ y, 0.5f + z, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,


	};

	float bok2[] = {


		-0.5f + x, 1.0f + y, -0.5f + z, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f + x, 1.0f + y, -0.5f + z, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f + x, 0.0f + y, -0.5f + z, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f + x, 0.0f + y, -0.5f + z, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	};

	float bok3[] = {


		0.5f + x, 1.0f + y, 0.5f + z, 1.0f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f + x, 1.0f + y, 0.5f + z, 1.0f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f + x, 0.0f + y, 0.5f + z, 1.0f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f + x, 0.0f + y, 0.5f + z, 1.0f, 0.5f, 0.5f, 1.0f, 0.0f,
	};

	float bok4[] = {


		-0.5f+ x, 1.0f+ y, -0.5f + z, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f+ x, 1.0f+ y, 0.5f + z, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f+ x, 0.0f+ y, 0.5f + z, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f+ x, 0.0f+ y, -0.5f + z, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,


	};

	Model* O1 = new Model(narys, sizeof(narys) / sizeof(narys[0]));
	Model* O2 = new Model(spodek, sizeof(spodek) / sizeof(spodek[0]));
	Model* O4 = new Model(bok2, sizeof(bok2) / sizeof(bok2[0]));
	Model* O5 = new Model(bok3, sizeof(bok3) / sizeof(bok3[0]));


	O1->rot_x = rot_x;
	O1->rot_y = rot_y;
	O1->rot_z = rot_z;

	O2->rot_x = rot_x;
	O2->rot_y = rot_y;
	O2->rot_z = rot_z;

	O4->rot_x = rot_x;
	O4->rot_y = rot_y;
	O4->rot_z = rot_z;

	O5->rot_x = rot_x;
	O5->rot_y = rot_y;
	O5->rot_z = rot_z;

	O1->edges = 4;
	O2->edges = 4;
	O4->edges = 4;
	O5->edges = 4;

	O1->type = GL_POLYGON;
	O2->type = GL_POLYGON;
	O4->type = GL_POLYGON;
	O5->type = GL_POLYGON;

	VAO *_vao0 = new VAO(4, 4);
	VAO *_vao1= new VAO(4, 4);
	VAO *_vao2 = new VAO(4, 4);
	VAO *_vao3= new VAO(4, 4);
	O1->set_vao(_vao0);
	O2->set_vao(_vao1);
	O4->set_vao(_vao2);
	O5->set_vao(_vao3);

	Object* object = new Object();

	object->add_model(O1);
	object->add_model(O2);
	object->add_model(O4);
	object->add_model(O5);


	choose_shader(shader, object);
}

void RunGame::add_tree(const char* shader, float x, float y, float z, float rot_x, float rot_y, float rot_z, float scale_x, float scale_y, float scale_z, float static_rot_x=0, float static_rot_y=0, float static_rot_z=0) {
	
	Model* O1 = new Model(plain, sizeof(plain) / sizeof(plain[0]));
	
	VAO* _vao = new VAO(3, 3);
	//  glDrawArrays(GL_TRIANGLES, 0, 92814);
	O1->set_vao(_vao);
	O1->edges = 92814;
	O1->type = GL_TRIANGLES;

	Object* object = new Object();
	object->add_model(O1, x, y, z, rot_x, rot_y, rot_z, scale_x , scale_y, scale_z , static_rot_x, static_rot_y, static_rot_z);
	choose_shader(shader, object);

}

void RunGame::add_plain(const char* shader, float x, float y, float z) {

	float spodek[] = {

	50.5f + x, 0.0f + y, 50.5f + z, 1.0f, 0.0f, 0.5f, 0.0f, 0.0f,
	50.5f + x, 0.0f + y, -50.5f + z, 1.0f, 0.0f, 0.5f, 0.0f, 0.0f,
	-50.5f + x, 0.0f + y, -50.5f + z, 1.0f, 0.0f, 0.5f, 0.0f, 0.0f,
	-50.5f + x, 0.0f + y, 50.5f + z, 1.0f, 0.0f, 0.5f, 0.0f, 0.0f,


	};

	Model* O1 = new Model(spodek, sizeof(spodek) / sizeof(spodek[0]));

	VAO* _vao = new VAO(4, 4);
	//  glDrawArrays(GL_TRIANGLES, 0, 92814);
	O1->set_vao(_vao);
	O1->edges = 4;
	O1->type = GL_POLYGON;

	Object* object = new Object();
	object->add_model(O1, x, y, z, 0, 0, 0);
	choose_shader(shader, object);

}

void RunGame::add_gift(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z) {



	Model* O1 = new Model(plain_gift, sizeof(plain_gift) / sizeof(plain_gift[0]));

	VAO *_vao = new VAO(3, 3);

	O1->set_vao(_vao);
	O1->edges = 66624;
	O1->type = GL_POLYGON;

	Object* object = new Object();
	object->add_model(O1, x, y, z, 0, 0, 0, scale_x, scale_y, scale_z);
	choose_shader(shader, object);

}

void RunGame::add_bush(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z)
{
	Model* O1 = new Model(plain_bush, sizeof(plain_bush) / sizeof(plain_bush[0]));

	VAO *_vao = new VAO(3, 3);

	O1->set_vao(_vao);
	O1->edges = 8730;
	O1->type = GL_POLYGON;

	Object* object = new Object();
	object->add_model(O1, x, y, z, 0, 0, 0, scale_x, scale_y, scale_z);
	choose_shader(shader, object);
}

void RunGame::add_texture_plain(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z)
{
	Model* O1 = new Model(texture_plain, sizeof(texture_plain) / sizeof(texture_plain[0]));

	TextureVAO* _vao = new TextureVAO(3, 3, 2);

	O1->set_vao(_vao);
	O1->edges = 6;
	O1->type = GL_POLYGON;

	TextureObject* object = new TextureObject(TEXTURE_WOOD_ID);
	object->add_model(O1, x, y, z, 0, 0, 0, scale_x, scale_y, scale_z);
	choose_shader(shader, object);
}

void RunGame::add_building(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z)
{
	

	Model* O1 = new Model(building, sizeof(building) / sizeof(building[0]));

	TextureVAO* _vao = new TextureVAO(3, 3, 2);

	O1->set_vao(_vao);
	O1->edges = 6636;
	O1->type = GL_TRIANGLES;

	TextureObject* object = new TextureObject(TEXTURE_BUILDING_ID);
	object->add_model(O1, x, y, z, 0, 0, 0, scale_x, scale_y, scale_z);
	choose_shader(shader, object);
}

void RunGame::add_skydome(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z)
{
	Model* O1 = new Model(skydome, sizeof(skydome) / sizeof(skydome[0]));

	TextureVAO* _vao = new TextureVAO(3, 3, 2);

	O1->set_vao(_vao);
	O1->edges = 1440;
	O1->type = GL_TRIANGLES;

	TextureObject* object = new TextureObject(TEXTURE_SKYDOME_ID);
	object->add_model(O1, x, y, z, 0, 0, 0, scale_x, scale_y, scale_z);
	choose_shader(shader, object);
}

void RunGame::add_zombie(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z,  bool is_bezier, glm::mat4 p_A, glm::mat4x3 p_B)
{
	Model* O1 = new Model("models/zombie.obj");
	O1->is_moving_using_bezier = is_bezier;
	O1->A = p_A;
	O1->B = p_B;
	TextureVAO* k = new TextureVAO(3, 3, 2);
	O1->set_vao(k);
	O1->type = GL_TRIANGLES;

	TextureObject* object = new TextureObject(TEXTURE_ZOMBIE_ID);
	object->add_model(O1, x, y, z, 0, 0, 0, scale_x, scale_y, scale_z);
	object->name = "zombie";
	choose_shader(shader, object);


}

void RunGame::add_woodbox_from_blender(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z)
{
	Model* O1 = new Model("models/WoodBox.fbx");

	TextureVAO* k = new TextureVAO(3, 3, 2);
	O1->set_vao(k);
	O1->type = GL_TRIANGLES;

	TextureObject* object = new TextureObject(TEXTURE_BLEND_WOOD_BOX);
	object->add_model(O1, x, y, z, 0, 0, 0, scale_x, scale_y, scale_z);
	object->name = "my_wood_box";
	choose_shader(shader, object);
}

void RunGame::add_chair_from_blender(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z)
{
	Model* O1 = new Model("models/Zidle.fbx");

	TextureVAO* k = new TextureVAO(3, 3, 2);
	O1->set_vao(k);
	O1->type = GL_TRIANGLES;

	TextureObject* object = new TextureObject(TEXTURE_BLEND_CHAIR);
	object->add_model(O1, x, y, z, 0, 0, 0, scale_x, scale_y, scale_z);
	object->name = "chair";
	choose_shader(shader, object);


}

void RunGame::add_cube_from_blender(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z)
{
	Model* O1 = new Model("models/kostkaBake.obj");

	TextureVAO* k = new TextureVAO(3, 3, 2);
	O1->set_vao(k);
	O1->type = GL_TRIANGLES;

	TextureObject* object = new TextureObject(TEXTURE_BLEND_CUBE);
	object->add_model(O1, x, y, z, 0, 0, 0, scale_x, scale_y, scale_z);
	object->name = "my_cube";
	choose_shader(shader, object);


}
void RunGame::add_lady_cat_from_blender(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z)
{
	Model* O1 = new Model("models/LadyCat.fbx");

	TextureVAO* k = new TextureVAO(3, 3, 2);
	O1->set_vao(k);
	O1->type = GL_TRIANGLES;

	TextureObject* object = new TextureObject(TEXTURE_BLEND_LADYCAT);
	object->add_model(O1, x, y, z, 0, 0, 0, scale_x, scale_y, scale_z);
	object->name = "ladycat";
	choose_shader(shader, object);
}

void RunGame::add_anime_from_blender(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z)
{
	Model* O1 = new Model("models/Anime_character.fbx");

	TextureVAO* k = new TextureVAO(3, 3, 2);
	O1->set_vao(k);
	O1->type = GL_TRIANGLES;

	TextureObject* object = new TextureObject(TEXTURE_BLEND_ANIME);
	object->add_model(O1, x, y, z, 0, 0, 0, scale_x, scale_y, scale_z);
	object->name = "anime";
	choose_shader(shader, object);
}
void RunGame::add_cube_shadow_from_blender(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z) {
	Model* O1 = new Model("models/Stiny/ShadowCube.fbx");

	TextureVAO* k = new TextureVAO(3, 3, 2);
	O1->set_vao(k);
	O1->type = GL_TRIANGLES;

	TextureObject* object = new TextureObject(TEXTURE_BLEND_SHADOWCUBE);
	object->add_model(O1, x, y, z, 0, 0, 0, scale_x, scale_y, scale_z);
	object->name = "shadowcube";
	choose_shader(shader, object);
}
void RunGame::add_table_shadow_from_blender(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z) {
	Model* O1 = new Model("models/Stiny/ShadowTable.fbx");

	TextureVAO* k = new TextureVAO(3, 3, 2);
	O1->set_vao(k);
	O1->type = GL_TRIANGLES;

	TextureObject* object = new TextureObject(TEXTURE_BLEND_SHADOWTABLE);
	object->add_model(O1, x, y, z, 0, 0, 0, scale_x, scale_y, scale_z);
	object->name = "shadowtable";
	choose_shader(shader, object);
}
void RunGame::add_plain_shadow_from_blender(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z) {
	Model* O1 = new Model("models/Stiny/ShadowPlain.fbx");

	TextureVAO* k = new TextureVAO(3, 3, 2);
	O1->set_vao(k);
	O1->type = GL_TRIANGLES;

	TextureObject* object = new TextureObject(TEXTURE_BLEND_SHADOWPLAIN);
	object->add_model(O1, x, y, z, 0, 0, 0, scale_x, scale_y, scale_z);
	object->name = "shadowplain";
	choose_shader(shader, object);
}


void RunGame::add_teren_from_blender(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z)
{
	Model* O1 = new Model("models/teren.fbx");

	TextureVAO* k = new TextureVAO(3, 3, 2);
	O1->set_vao(k);
	O1->type = GL_TRIANGLES;

	TextureObject* object = new TextureObject(TEXTURE_BLEND_TEREN);
	object->add_model(O1, x, y, z, 0, 0, 0, scale_x, scale_y, scale_z);
	object->name = "teren";
	choose_shader(shader, object);


}

void RunGame::add_tower_baked_shadow(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z)
{
	Model* O1 = new Model("models/BlenderFinal/WatchTower.fbx");

	TextureVAO* k = new TextureVAO(3, 3, 2);
	O1->set_vao(k);
	O1->type = GL_TRIANGLES;

	TextureObject* object = new TextureObject(TEXTURE_BAKED_SHADOW_TOWER);
	object->add_model(O1, x, y, z, 0, 0, 0, scale_x, scale_y, scale_z);
	object->name = "tower";
	choose_shader(shader, object);


}

void RunGame::add_texture_object(const char* path, float x, float y, float z, float scale_x, float scale_y, float scale_z) {
	Model* O1 = new Model(path);
	TextureVAO* k = new TextureVAO(3, 3, 2);
	O1->set_vao(k);
	O1->type = GL_TRIANGLES;

	TextureObject* object = new TextureObject(TEXTURE_TREE_ID);
	object->add_model(O1, x, y, z, 0, 0, 0, scale_x, scale_y, scale_z);
	object->name = path;
	choose_shader("texture", object);
}

void RunGame::add_plain_from_file(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z)
{
	Model* O1 = new Model("models/plane.obj");

	TextureVAO* k = new TextureVAO(3, 3, 2);
	O1->set_vao(k);
	O1->type = GL_TRIANGLES;

	TextureObject* object = new TextureObject(TEXTURE_WOOD_ID);
	object->add_model(O1, x, y, z, 0, 0, 0, scale_x, scale_y, scale_z);
	choose_shader(shader, object);

}

void RunGame::add_tree_from_file(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z)
{
	Model* O1 = new Model("models/tree.obj");
	TextureVAO* k = new TextureVAO(3, 3, 2);
	O1->set_vao(k);
	O1->type = GL_TRIANGLES;

	TextureObject* object = new TextureObject(TEXTURE_TREE_ID);
	object->add_model(O1, x, y, z, 0, 0, 0, scale_x, scale_y, scale_z);
	object->name = "strom";
	choose_shader(shader, object);
}

void RunGame::add_skybox(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z)
{
	Model* O1 = new Model("models/skybox.obj");
	TextureVAO* k = new TextureVAO(3, 3, 2);
	O1->set_vao(k);
	O1->type = GL_TRIANGLES;

	TextureObject* object = new TextureObject(TEXTURE_SKYBOX_ID);
	object->add_model(O1, x, y, z, 0, 0, 0, scale_x, scale_y, scale_z);
	choose_shader(shader, object);
}

void RunGame::add_teren_with_grass(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z)
{
	Model* O1 = new Model("models/teren/teren.obj");
	TextureVAO *k = new TextureVAO(3, 3, 2);
	O1->set_vao(k);
	O1->type = GL_TRIANGLES;
	
	TextureObject* object = new TextureObject(TEXTURE_TEREN_GRASS_ID);
	object->add_model(O1, x, y, z, 0, 0, 0, scale_x, scale_y, scale_z);
	object->spec_intensity = 0.1;
	object->name = "teren";
	choose_shader(shader, object);
}



void RunGame::add_ball_with_normal_map(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z)
{
	Model* O1 = new Model("model.obj");
	TangentVAO* k = new TangentVAO(3, 3, 2, 3);
	O1->set_vao(k);
	O1->type = GL_TRIANGLES;

	Object* object = new Object();
	object->add_model(O1, x, y, z, 0, 0, 0, scale_x, scale_y, scale_z);
	object->name = "ball_normal_map";
	choose_shader(shader, object);
}

void RunGame::add_wall(const char* shader, float x, float y, float z, float scale_x, float scale_y, float scale_z)
{
	Model* O1 = new Model("models/zed/zed.obj");
	TextureVAO* k = new TextureVAO(3, 3, 2);
	O1->set_vao(k);
	O1->type = GL_TRIANGLES;

	TextureObject* object = new TextureObject(TEXTURE_WALL_ID);
	object->add_model(O1, x, y, z, 0, 0, 0, scale_x, scale_y, scale_z , 0,0,0);
	object->name = "wall";
	object->spec_intensity = 0.01;
	choose_shader(shader, object);
}



