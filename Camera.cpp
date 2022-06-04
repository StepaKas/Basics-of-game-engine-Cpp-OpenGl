#include"Camera.h"
#include"shader.h"
#include "RunGame.h"
Camera* Camera::cam = 0;


Camera::Camera(int width, int height, glm::vec3 position) : 
	width(width), height(height), Position(position)
{

}

void Camera::init_instance(int width, int height, glm::vec3 position) {

	if (cam == 0)
	{
		cam = new Camera(width, height, position);
	}

};

Camera* Camera::return_instance() {
	return cam;
}




void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{

	view = glm::mat4(1.0f);
	


	view = glm::lookAt(Position, Position + Orientation, Up);
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);	
	cameraMatrix = projection * view;
}

void Camera::Matrix(Shader* shader, const char* uniform) {

	shader->uniform_matrix(uniform, cameraMatrix);

}

void Camera::Inputs(GLFWwindow* window)
{

	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
	{
		shooting = !shooting;
		cout << "Shooting changed\n";
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += speed * -glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += speed * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += speed * glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += speed * Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Position += speed * -Up;
	}
	
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 0.1f;
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	
		if (firstClick)
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}

		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		
		//Aby se uhel kamery nepøestìlil
		if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			Orientation = newOrientation;
		}
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);


		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {

		if (rightCLickFirst) {
			GLbyte color[4];
			GLfloat depth;
			GLuint index;

			double mouseX;
			double mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);

			GLint x = (GLint)mouseX;
			GLint y = (GLint)mouseY;
			int newy = height  - y -10;

			glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
			glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
			glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

			printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n", x, y, color[0], color[1], color[2], color[3], depth, index);

			//Mùžeme nastavit vybrané tìleso scena->setSelect(index-1);

			//Mùžeme vypoèíst pozici v globálním souøadném systému.  
			glm::vec3 screenX = glm::vec3(x, newy, depth);


			glm::vec4 viewPort = glm::vec4(0, 0, width, height);
			glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

			printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);
			if (shooting) {
				// strilim
				int rand0_3 = rand() % 3;


				if (rand0_3 == 0) {
					bool played = PlaySound(TEXT("sounds/boom0.wav"), NULL, SND_FILENAME | SND_ASYNC);
				}
				else if (rand0_3 == 1) {
					bool played = PlaySound(TEXT("sounds/boom1.wav"), NULL, SND_FILENAME | SND_ASYNC);
				}
				else if (rand0_3 == 2) {
					bool played = PlaySound(TEXT("sounds/boom3.wav"), NULL, SND_FILENAME | SND_ASYNC);
				}

				for (int i = 0; i < RunGame::return_instance()->objecty_texture_shader.size(); i++) {
					//	cout << RunGame::return_instance()->objecty_texture_shader[i]->name << " " << RunGame::return_instance()->objecty_texture_shader[i]->id << endl;
					if (RunGame::return_instance()->objecty_texture_shader[i]->name == "zombie" && RunGame::return_instance()->objecty_texture_shader[i]->id == index) {
						cout << "Objekt smazan" << endl;
						//	bool played = PlaySound((L"sounds/zomb_dead.wav"), NULL, SND_FILENAME |  SND_ASYNC);

						RunGame::return_instance()->objecty_texture_shader[i]->id = -1;
					}
				}
			
			}
			else if (!shooting) {
				//sazim
				for (int i = 0; i < RunGame::return_instance()->objecty_texture_shader.size(); i++) {
					if (RunGame::return_instance()->objecty_texture_shader[i]->name == "teren" && RunGame::return_instance()->objecty_texture_shader[i]->id == index) {
						RunGame::return_instance()->add_tree_from_file("texture", pos.x, pos.y, pos.z, 1,1,1);
						RunGame::return_instance()->objecty_texture_shader[RunGame::return_instance()->objecty_texture_shader.size() - 1]->init_models(RunGame::return_instance()->texture_shader);
						bool played = PlaySound(TEXT("sounds/chop_wood.wav"), NULL, SND_FILENAME | SND_ASYNC);
						break;
					}
				}

			}
			//RunGame::return_instance()->add_tree_from_file("texture", pos.x, pos.y, pos.z, 1, 1, 1);	
			//RunGame::return_instance()->objecty_texture_shader[RunGame::return_instance()->objecty_texture_shader.size() - 1]->init_models(RunGame::return_instance()->texture_shader);

			rightCLickFirst = false;
		}




	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
	{
		
		rightCLickFirst = true;
	}
}

void Camera::change_width_height(int new_width, int new_height) 
{
	width = new_width;
	height = new_height;
}
