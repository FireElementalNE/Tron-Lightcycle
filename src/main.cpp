#include <iostream>
#include <fstream>
#include <GL\glut.h>
#include "lightCycle.h"
#define DEBUG false
using namespace std;

const int CANVAS_WIDTH = 800;
const int CANVAS_HEIGHT = 800;

ofstream file;
LightCycle bike = LightCycle(CANVAS_WIDTH, CANVAS_HEIGHT, DEBUG);

void printMouse(int button, int state, int x, int y) {
	if(button == GLUT_LEFT_BUTTON) {
		float x1 = x*(2.0f / 800.0f) - 1.0f;
		float y1 = -1.0f * y*(2.0f / 800.0f) + 1.0f;
		file << "glVertex2f(" << x1 << ", " << y1 << ");\n";
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	bike.drawBike();
	glFlush();
}

int main(int argc, char** argv) {
	if (DEBUG) {
		file.open("out.txt");
	}
	glutInit(&argc, argv);
	bike.initBike();
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(CANVAS_WIDTH, CANVAS_HEIGHT);
	glutCreateWindow("Tron Light Cycle");
	glutDisplayFunc(display);
	if (DEBUG) {
		glutMouseFunc(printMouse);
	}
	glutMainLoop();
	if (DEBUG) {
		file.close();
	}
}