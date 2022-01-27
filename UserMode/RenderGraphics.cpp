#include "RenderGraphics.h"
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

GLFWwindow* CreateGLWindow(int windowX, int windowY) {
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return nullptr;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(windowX, windowY, "Sonar", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	return window;
}

GLTtext* CreateGLText() {
	if (!gltInit())
	{
		fprintf(stderr, "Failed to initialize glText\n");
		glfwTerminate();
		return nullptr;
	}

	GLTtext* text = gltCreateText();
	return text;
}

void drawWindow(GLFWwindow* window, std::vector<Vector3> PointsToRender) {
	if (glfwWindowShouldClose(window)) glfwTerminate();

	//while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//glClearColor(1.0, 1.0, 1.0, 1.0); //background color
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_LINES);
		glVertex2f(-1.0f, 0.0f);
		glVertex2f(1.0f, 0.0f);
		glVertex2f(0.0f, -1.0f);
		glVertex2f(0.0f, 1.0f);
		glEnd();

		glPointSize(10);
		if (PointsToRender.size() > 0) {
			for (int i = 0; i < PointsToRender.size(); i++) {
				if (PointsToRender[i].z == 1.0) {		//ENEMY
					glColor3f(1.0, 0.0, 0.0);	//red
				}
				else {
					glColor3f(0.0, 0.0, 1.0);	//blue
				}

				glBegin(GL_POINTS);
				glVertex2f(PointsToRender[i].x, PointsToRender[i].y);
				glEnd();

				glColor3f(1.0, 1.0, 1.0);
			}
		}

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
}

void initWindow(GLFWwindow* window) {
	if (glfwWindowShouldClose(window)) glfwTerminate();
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_LINES);
	glVertex2f(-1.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);
	glVertex2f(0.0f, -1.0f);
	glVertex2f(0.0f, 1.0f);
	glEnd();

	/* Swap front and back buffers */
	glfwSwapBuffers(window);

	/* Poll for and process events */
	glfwPollEvents();
}

int DrawRadar() {
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(800, 800, "Sonar", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void Radar::setColor(std::string color) {
		std::transform(color.begin(), color.end(), color.begin(), ::toupper);

		if (color.compare("RED") == 0) {
			glColor3f(1.0, 0.0, 0.0);
		}
		else if (color.compare("GREEN") == 0) {
			glColor3f(0.0, 1.0, 0.0);
		}
		else if (color.compare("BLUE") == 0) {
			glColor3f(0.0, 0.0, 1.0);
		}
		else if (color.compare("PURPLE") == 0) {
			glColor3f(0.5, 0.0, 1.0);
		}
		else if (color.compare("YELLOW") == 0) {
			glColor3f(1.0, 1.0, 0.0);
		}
		else if (color.compare("ORANGE") == 0) {
			glColor3f(1.0, 0.5, 0.0);
		}
		else if ("WHITE") {
			glColor3f(1.0, 1.0, 1.0);
		}
		else {
			glColor3f(1.0, 1.0, 1.0);
		}
	}

void Radar::drawFilledCircle(GLfloat x, GLfloat y, float size, std::string color) {
	setColor(color);

	int i;
	int triangleAmount = 20; //# of triangles used to draw circle
	GLfloat radiusX = (size / this->windowX);
	GLfloat radiusY = (size / this->windowY);

	GLfloat twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radiusX * cos(i * twicePi / triangleAmount)),
			y + (radiusY * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
}

void Radar::drawHollowCircle(GLfloat x, GLfloat y, float size, std::string color) {
	setColor(color);
	int i;
	int lineAmount = 100; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;
	GLfloat radiusX = (size / this->windowX);
	GLfloat radiusY = (size / this->windowY);

	glBegin(GL_LINE_LOOP);
	for (i = 0; i <= lineAmount; i++) {
		glVertex2f(
			x + (radiusX * cos(i * twicePi / lineAmount)),
			y + (radiusY * sin(i * twicePi / lineAmount))
		);
	}
	glEnd();
}

void Radar::drawTriangle(GLfloat x, GLfloat y, float size, std::string color, bool down) {
	setColor(color);

	//1: down half y, right half x
	//2: down half y, left half x
	//3: up half y
	//x + (size / this->windowX)
	size = size * 2;
	float xDistance = (size / this->windowX);
	float yDistance = (size / this->windowY);
	glBegin(GL_TRIANGLES);
	if (!down) {
		glVertex3f(x - (xDistance / 2), y - (yDistance / 2), 0);
		glVertex3f(x + (xDistance / 2), y - (yDistance / 2), 0);
		glVertex3f(x, y + (yDistance / 2), 0);
	}
	else {
		glVertex3f(x - (xDistance / 2), y + (yDistance / 2), 0);
		glVertex3f(x + (xDistance / 2), y + (yDistance / 2), 0);
		glVertex3f(x, y - (yDistance / 2), 0);
	}
	glEnd();
}

void Radar::drawText(GLfloat x, GLfloat y, float size, std::string type) {
	gltSetText(this->text, type.c_str());
	gltBeginDraw();

	// Draw any amount of text between begin and end
	gltColor(1.0f, 1.0f, 1.0f, 1.0f);
	gltDrawText2DAligned(text, x, y, size,GLT_CENTER, GLT_BOTTOM);

	// Finish drawing text
	gltEndDraw();

}

float pixelToPoint(float pixelPoint, int windowSize) {
	int halfWindow = windowSize / 2;
	return (pixelPoint - halfWindow) / halfWindow;
}

float pointToPixel(float point, int windowSize) {
	int halfWindow = windowSize / 2;
	return (point * halfWindow + halfWindow);
}

float pixelDistToPoint(float pixelDist, int windowSize) {
	return pixelDist/windowSize;
}

void Radar::drawRect(GLfloat x, GLfloat y, float length, float height, std::string color, float percent, std::string alignment) {
	setColor(color);
	float left = x - (length / 2.0);
	float right = left + length * percent;
	float top = y + (height / 2.0);
	float bottom = y - (height / 2.0);
	glBegin(GL_POLYGON);
	glVertex3f(left, top,0);
	glVertex3f(left, bottom,0);
	glVertex3f(right, bottom,0);
	glVertex3f(right, top,0);
	glEnd();
}

void Radar::drawHealthBar(GLfloat x, GLfloat y,float size, float percent, float yOffset) {
	std::string color;
	if (percent > .5) {
		color = "GREEN";
	}
	else if (percent > .2 && percent >= .5) {
		color = "YELLOW";
	}
	else {
		color = "RED";
	}

	yOffset = pixelDistToPoint(yOffset, this->windowY);
	float healthBarYSpacing = (size/this->windowY) + yOffset;
	float length = (size / this->windowX) * 2;
	float height = (size / this->windowY) / 5;
	//drawRect(x, y - healthBarYSpacing, length + yOffset/2, height + yOffset/2, "WHITE");

	drawRect(x, y - healthBarYSpacing, length, height, color, percent);
}

void Radar::renderBlip(Blip blip) {
	this->drawFilledCircle(blip.x, blip.y, blip.size, blip.color);
	//x, y, length, height, color, percent
	if (blip.health) {
		this->drawHealthBar(blip.x, blip.y, blip.size, 1.0);
	}
}

void Radar::renderBlipName(Blip blip) {

	drawText(pointToPixel(blip.x, this->windowX), pointToPixel(blip.y, this->windowY) - blip.size / 2, .8, blip.name);
}

void Radar::createPlayerBlips(EFTPlayer player) {

	if (player.name.empty()) {
		Blip blip = Blip(player.type, pixelToPoint(player.headPos.x, this->windowX), pixelToPoint(player.headPos.y, this->windowY), "ORANGE", 10, 0);
		blipList.emplace_back(blip);
	}
	else {
		Blip blip = Blip(player.name, pixelToPoint(player.headPos.x, this->windowX), pixelToPoint(player.headPos.y, this->windowY), "RED", 10, 0);
		blipList.emplace_back(blip);
	}
}

void Radar::createLootBlips(EFTLoot loot) {
	Blip blip = Blip(loot.name, pixelToPoint(loot.origin.x, this->windowX), pixelToPoint(loot.origin.y, this->windowY), "YELLOW", 10, 0);
	blipList.emplace_back(blip);
}

void Radar::setRange(int range) {
	this->range = range;
}

void Radar::setMiddle(Vector3 middle) {
	this->middle = middle;
}

void Radar::drawWindowTesting() {
	if (glfwWindowShouldClose(this->window)) glfwTerminate();

	//while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//glClearColor(1.0, 1.0, 1.0, 1.0); //background color
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_LINES);
		glVertex2f(-1.0f, 0.0f);
		glVertex2f(1.0f, 0.0f);
		glVertex2f(0.0f, -1.0f);
		glVertex2f(0.0f, 1.0f);
		glEnd();

		glPointSize(10);

		//drawFilledCircle(pixelToPoint(640, this->windowX), pixelToPoint(360, this->windowY), 50, "BLUE");

		//drawHollowCircle(0, 0, 10, "RED");
		//drawTriangle(.2, 0, 50, "RED", true);
		//Blip blip1 = Blip("BLM-or-DIE", pixelToPoint(640, this->windowX), pixelToPoint(360, this->windowY), "RED", 10, 1);
		//Blip blip2 = Blip("DonCheadle", pixelToPoint(200, this->windowX), pixelToPoint(360, this->windowY), "RED", 10, 1);
		//Blip blip3 = Blip("Bitcoin", pixelToPoint(400, this->windowX), pixelToPoint(360, this->windowY), "YELLOW", 10, 0);

		//renderBlip(blip1);
		//renderBlipName(blip1);

		for (int i = 0; i < this->blipList.size(); i++) {
			renderBlip(this->blipList[i]);
		}
		for (int i = 0; i < this->blipList.size(); i++) {
			//renderBlipName(this->blipList[i]);
			break;
		}

		//gltBeginDraw();
		//drawText(-.5, 0, 1.0, "Poggers");
		//drawText(100, 100, 1.0, "Poggers2");
		//gltEndDraw();
		/*
		if (PointsToRender.size() > 0) {
			for (int i = 0; i < PointsToRender.size(); i++) {
				if (PointsToRender[i].z == 1.0) {		//ENEMY
					glColor3f(1.0, 0.0, 0.0);	//red
				}
				else {
					glColor3f(0.0, 0.0, 1.0);	//blue
				}

				glBegin(GL_POINTS);
				glVertex2f(PointsToRender[i].x, PointsToRender[i].y);
				glEnd();

				glColor3f(1.0, 1.0, 1.0);
			}
		}
		*/

		/* Swap front and back buffers */
		glfwSwapBuffers(this->window);

		/* Poll for and process events */
		glfwPollEvents();
	}
}

void Radar::closeWindow() {
	glfwTerminate();
}