#pragma once
#include "TangentVAO.h"



class Model {
protected:

	
	GLuint VBO = 0;
    GLuint IBO = 0;

	float rotation = 0.0f;
	double prevTime = glfwGetTime();
	VAO * m_VAO ;
	glm::mat4 model = glm::mat4(1.0f);

	// pro pohyb na krivce



	float t = 0.5f;
	float t_up = 1.0f;
	float t_down = -1.0f;

	float delta = 0.01;
	bool changed_dirr = false;
	static int zomb_edges;
	static float zomb_points[1000000];
	static int zomb_size;

	static int tree_edges;
	static float tree_points[1000000];
	static int tree_size;

public:

	bool is_moving_using_bezier = false;

	glm::mat4 A = glm::mat4(glm::vec4(-1.0, 3.0, -3.0, 1.0),
		glm::vec4(3.0, -6.0, 3.0, 0),
		glm::vec4(-3.0, 3.0, 0, 0),
		glm::vec4(1, 0, 0, 0));
	//   std::cout << glm::to_string(A) << std::endl;
	glm::mat4x3 B = glm::mat4x3(glm::vec3(0, 0, 0),
		glm::vec3(2, 2, 0),
		glm::vec3(4, 4, 0),
		glm::vec3(6, 0, 0));


	float  points[1000000];
    int points_size;
	float x, y, z = 0;
	float x_m, y_m, z_m= 0;
	float scale_x = 1;
	float scale_y = 1;
	float scale_z = 1;
	float rot_x = 0;
	float rot_y = 0;
	float rot_z = 0;

	float static_rot_x = 0;
	float static_rot_y = 0;
	float static_rot_z = 0;
	Shader* shader;

	// GL_POLYGON, GL_TRIANGLES
	GLenum type = GL_TRIANGLES;
	int edges = 0;

    int indicesCount = 0;

    Vertex* pVertices;

	void load(std::string fileName);

    //  load("test.obj");

    //  vykresleni pomoci index bufferu
    //  glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, NULL);


	Model(string fileName);
	
	Model(float field[], int size)
	{
		for (size_t i = 0; i < size; i++){
			points[i] = field[i];
		}
		int points_size = size;
	}
	Model() {

	}
	void init_VBO() {
  
		VBO = 0;

		glGenBuffers(1, &VBO); // generate the VBO

		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	}

	void set_vao(VAO* vao) {
		m_VAO = vao;
	}
	void  init_VAO()  {

		m_VAO->init_VAO(VBO);
		

	}

	// in endless while
	void run_in_loop( float center_x, float center_y, float center_z , int text_id = 0) {
	
		model = glm::mat4(1.0f);

	
		model = glm::translate(model, glm::vec3(x, y, z));
		model = glm::scale(model, glm::vec3(scale_x, scale_y, scale_z));
		x_m = x;
		y_m = y;
		z_m = z;

		if (is_moving_using_bezier) {
			glm::vec4 parameters = glm::vec4(t * t * t, t * t, t, 1.0f);
			if (t >= t_up || t <= t_down) {

				delta *= -1;

			}
			t += delta;

			glm::vec4 parameters_next_position = glm::vec4(t * t * t, t * t, t, 1.0f);

			glm::vec3 p = parameters * A * glm::transpose(B);
			glm::vec3 p_new_pos = parameters_next_position * A * glm::transpose(B);
			glm::vec3 direction_of_next_move = glm::normalize( p_new_pos - p);
			model = glm::translate(glm::mat4(1.0f), p  + glm::vec3(x, y, z));
			x_m = p.x + x;
			y_m = p.y + y;
			z_m = p.z + z;
		//	model = glm::rotate(model, 3.14159f * direction_of_next_move.x, glm::vec3(1, 0, 0));
			float angl = glm::angle(glm::vec2(1,0),(glm::vec2(direction_of_next_move.x, direction_of_next_move.z)));
	
			if (direction_of_next_move.z > 0) {
				angl *= -1;
			}
		//	cout << "X: " << direction_of_next_move.x << " Y: " << direction_of_next_move.y << " Z: " << direction_of_next_move.z << " Angl: " << angl << endl;
			model = glm::rotate(model, (3.14159f/2) + ( angl), glm::vec3(0, 1, 0));
			
			//model = glm::rotate(model, 3.14159f * direction_of_next_move.z, glm::vec3(0, 0, 1));
			model = glm::scale(model, glm::vec3(scale_x, scale_y, scale_z));

		
		}


		glBindVertexArray(m_VAO->ID);



		
		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60) {
			rotation += 0.5f;
			prevTime = crntTime;
		}




		//printf("%f %f %f\n", static_rot_x, static_rot_y, static_rot_z);
		if (!(static_rot_x == 0 && static_rot_y == 0 && static_rot_z == 0))
		{
			model = glm::translate(model, glm::vec3(center_x, center_y, center_z));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(static_rot_x, static_rot_y, static_rot_y));
			model = glm::translate(model, glm::vec3(-center_x, -center_y, -center_z));
		}


		if (rot_x == 0 && rot_y == 0 && rot_z == 0) {

		}
		else
		{
			model = glm::translate(model, glm::vec3(center_x, center_y, center_z));
			model = glm::rotate(model, glm::radians(rotation), glm::vec3(rot_x, rot_y, rot_z));
			model = glm::translate(model, glm::vec3(-center_x, -center_y, -center_z));
		}
		
		int modelloc = shader->modelloc();
		glUniformMatrix4fv(modelloc, 1, GL_FALSE, glm::value_ptr(model));
		glm::mat4 tan_model = glm::mat4(1.0);
		shader->modellocTangent(tan_model);
	
		
		glDrawArrays(type, 0, edges);
		
		

		

	}

};

