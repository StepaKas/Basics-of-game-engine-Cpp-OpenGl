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

#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags
//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <stdexcept>

#include <windows.h>
#include <mmsystem.h>


#include "shader.h"


enum {
	TEXTURE_WOOD_ID,
	TEXTURE_BUILDING_ID,
	TEXTURE_SKYDOME_ID,
	TEXTURE_ZOMBIE_ID,
	TEXTURE_TREE_ID,
	TEXTURE_SKYBOX_ID,
	TEXTURE_TEREN_GRASS_ID,
	TEXTURE_ALBEDO_ID,
	TEXTURE_NORMAL_MAP_ID,
	TEXTURE_WALL_ID,
	TEXTURE_BLEND_CUBE,
	TEXTURE_BLEND_WOOD_BOX,
	TEXTURE_BLEND_CHAIR,
	TEXTURE_BLEND_TEREN,
	TEXTURE_BLEND_LADYCAT,
	TEXTURE_BLEND_ANIME,
	TEXTURE_BLEND_SHADOWCUBE,
	TEXTURE_BLEND_SHADOWTABLE,
	TEXTURE_BLEND_SHADOWPLAIN,
	TEXTURE_BAKED_SHADOW_TOWER
};

enum {
	WINDOW_WIDTH = 640,
	WINDOW_HEIGHT = 480
};

static void error_callback(int error, const char* description) { fputs(description, stderr); }

class OpenGLInit
{
private:
	OpenGLInit() { 
		// can't touch this
	}
public:

	// Initializes OpenGl and returns window pf the main scene
	static GLFWwindow* init_all(int p_width = WINDOW_WIDTH, int p_heght = WINDOW_HEIGHT) {
		
		GLFWwindow* window;
		glfwSetErrorCallback(error_callback);
		if (!glfwInit()) {
			fprintf(stderr, "ERROR: could not start GLFW3\n");
			exit(EXIT_FAILURE);
		}
		window = glfwCreateWindow(p_width, p_heght, "ZPG", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			exit(EXIT_FAILURE);
		}
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);

		// start GLEW extension handler
		glewExperimental = GL_TRUE;
		glewInit();


		// get version info
		printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
		printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
		printf("Vendor %s\n", glGetString(GL_VENDOR));
		printf("Renderer %s\n", glGetString(GL_RENDERER));
		printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
		int major, minor, revision;
		glfwGetVersion(&major, &minor, &revision);
		printf("Using GLFW %i.%i.%i\n", major, minor, revision);

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		float ratio = width / (float)height;
		glViewport(0, 0, width, height);

		return window;
	}

};

