#pragma once

#include <GL/glew.h>
//Include GLFW  
#include <GLFW/glfw3.h>  

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <stdexcept>

class Shader;
// singleton
class Camera
{
private:
	Camera(int width, int height, glm::vec3 position);
	Camera() {}
	static Camera* cam;
	
public:

	glm::mat4 view;
    
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	bool firstClick = true;
	bool rightCLickFirst = true;
	bool shooting = true;
	int width;
	int height;


	float speed = 0.1f;
	float sensitivity = 100.0f;

	static void init_instance(int width, int height, glm::vec3 position);
	static Camera* return_instance();



	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);

	void Matrix(Shader* shader, const char* uniform);

	void Inputs(GLFWwindow* window);

	void change_width_height(int new_width, int new_height);
	void print_w_h() {
		printf("Width %d, height %d\n", width, height);
	}
};

