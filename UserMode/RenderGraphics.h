#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// FreeType Headers
//#include <ft2build.h>
//#include FT_FREETYPE_H 

#include <vector>

#include <string>
#include "myMath.h"


int DrawRadar();
void closeWindow();
void drawWindow(GLFWwindow* window, std::vector<Vector3> NearbyPlayersInfo);
GLFWwindow* CreateGLWindow(int windowX, int windowY);
void initWindow(GLFWwindow* window);

class Radar {
	GLFWwindow* window;
	int windowX;
	int windowY;

	public:
		Radar(int sizeX, int sizeY) {
			this->windowX = sizeX;
			this->windowY = sizeY;
			this->window = CreateGLWindow(sizeX, sizeY);
		}

	void setColor(std::string color);
	void drawFilledCircle(GLfloat x, GLfloat y, float size, std::string color);
	void drawHollowCircle(GLfloat x, GLfloat y, float size, std::string color);

	void drawTriangle(GLfloat x, GLfloat y, float size, std::string color, bool down=false);
	void drawWindowTesting();
	void closeWindow();
};