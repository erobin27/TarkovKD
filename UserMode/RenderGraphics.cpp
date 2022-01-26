#include "RenderGraphics.h"
#include <stdio.h>
#include <string>
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

		drawFilledCircle(0, 0, 50, "BLUE");
		//drawHollowCircle(0, 0, 10, "RED");
		drawTriangle(.2, 0, 50, "RED", true);
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