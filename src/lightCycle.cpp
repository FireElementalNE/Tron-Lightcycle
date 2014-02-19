#include <iostream>
#include <vector>
#include <GL\glut.h>
#include "Posn.h"
#include "lightCycle.h"
static float CIRCLE_DISTANCE = 800.0f;
static float CIRCLE_OFFSET_Y = -200.0f;
static float CIRCLE_OFFSET_X = -100.0f;
static float INNER_CIRCLE_RADIUS = 125.0f;
static float OUTER_CIRCLE_RADIUS = 175.0f;

float * LightCycle::makeColor(float r, float g, float b) {
	float * myColor = (float*)malloc(3 * sizeof(float));
	myColor[0] = r;
	myColor[1] = g;
	myColor[2] = b;
	return myColor;
}

void LightCycle::initBike() {
	addFront();
	addBack();
	addBottomBar();
	addBottomDetails();
	addEngineBlock();
	addInnerCircles();
	addLayeredCircles();
}

void LightCycle::drawBike() {
	drawBottomDetails();
	drawBottomBar();
	drawEngineBlock();
	drawFront();
	drawBack();
	drawInnerCircles();
	drawLayeredCircles();
	drawDetails();
}

LightCycle::LightCycle(float w, float h, bool db) {
	c_width = w;
	c_height = h;
	innerCircleRadius = INNER_CIRCLE_RADIUS / w;
	outerCircleRadius = OUTER_CIRCLE_RADIUS / w;
	debug = db;
}
Component LightCycle::getComponent(string target) {
	for (vector <pair<string, Component> >::iterator itr = components.begin(); itr != components.end(); itr++) {
		if (target == itr->first) {
			return itr->second;
		}
	}
	cout << " could not find component " << target << endl;
	Component empty(0);
	return empty;
}
void LightCycle::addInnerCircles() {
	Posn leftInnerCircle(-1 * CIRCLE_DISTANCE / 2.0f, CIRCLE_OFFSET_Y);
	Posn rightInnerCircle(CIRCLE_DISTANCE / 2.0f, CIRCLE_OFFSET_Y);
	leftInnerCircle.setCanvas(c_width, c_height);
	rightInnerCircle.setCanvas(c_width, c_height);
	Component right = addInnerCircle(rightInnerCircle, GL_POLYGON);
	Component left = addInnerCircle(leftInnerCircle, GL_POLYGON);
	components.push_back(make_pair("LeftInnerCircle", left));
	components.push_back(make_pair("RightInnerCircle", right));
}
Component LightCycle::addPartialCircle(Posn coord, float radius, int start, int end, bool plus, int lastPosn, Component current) {
	if (plus) {
		for (int i = start; i < end; i++) {
			float theta = 2.0f * 3.1415926f * float(i) / float(360);
			float cx = radius * cosf(theta);
			float cy = radius * sinf(theta);
			Posn temp(coord.getXTransformed() + cx, coord.getYTransformed() + cy);
			current.addPoint(temp);
		}
	}
	else {
		for (int i = end; i > start; i--) {
			float theta = 2.0f * 3.1415926f * float(i) / float(360);
			float cx = radius * cosf(theta);
			float cy = radius * sinf(theta);
			Posn temp(coord.getXTransformed() + cx, coord.getYTransformed() + cy);
			current.addPoint(temp);
		}
	}
	return current;
}
Component LightCycle::addDashBoard(Component c) {
	c.addPoint(Posn(-0.625, -0.0675));
	c.addPoint(Posn(-0.64, -0.0475));
	c.addPoint(Posn(-0.6425, -0.0425));
	c.addPoint(Posn(-0.41, 0.06));
	c.addPoint(Posn(-0.3725, 0.0225));
	c.addPoint(Posn(-0.405, -0.0375));
	c.addPoint(Posn(-0.235, -0.0675));
	c.addPoint(Posn(-0.2875, -0.29));
	return c;
}
void LightCycle::addFront() {
	Component c(GL_POLYGON);
	Posn leftOuterCircle(-1 * CIRCLE_DISTANCE / 2.0f, CIRCLE_OFFSET_Y);
	leftOuterCircle.setCanvas(c_width, c_height);
	c = addPartialCircle(leftOuterCircle, outerCircleRadius, 125, 350, true, 350, c);
	c = addDashBoard(c);
	components.push_back(make_pair("Front", c));
}
Component LightCycle::addTrunk(Component c) {
	c.addPoint(Posn(0.58, -0.0433));
	c.addPoint(Posn(-0.0175, 0.1125));
	c.addPoint(Posn(0.22, -0.0649999));
	c.addPoint(Posn(0, -0.125));
	c.addPoint(Posn(0, -0.290));
	return c;
}
void LightCycle::addBack() {
	Component c(GL_POLYGON);
	Posn rightOuterCircle(CIRCLE_DISTANCE / 2.0f, CIRCLE_OFFSET_Y);
	rightOuterCircle.setCanvas(c_width, c_height);
	c = addPartialCircle(rightOuterCircle, outerCircleRadius, -170, 70, true, -168, c);
	c = addTrunk(c);
	components.push_back(make_pair("Back", c));
}
Component LightCycle::addCircle(Posn coord, float radius, int type) {
	Component c(type);
	for (unsigned int ii = 0; ii < 360; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(360);
		float cx = radius * cosf(theta) + 0.01f;
		float cy = radius * sinf(theta);
		Posn temp(coord.getXTransformed() + cx, coord.getYTransformed() + cy);
		c.addPoint(temp);
	}
	return c;
}
Component LightCycle::addInnerCircle(Posn coord, int type) {
	Component c(type);
	for (unsigned int ii = 0; ii < 360; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(360);
		float cx = innerCircleRadius * cosf(theta);
		float cy = innerCircleRadius * sinf(theta); 
		Posn temp(coord.getXTransformed() + cx, coord.getYTransformed() + cy);
		c.addPoint(temp);
	}
	return c;
}
void LightCycle::addEngineBlock() {
	Component c(GL_POLYGON);
	c.addPoint(Posn(-0.27, -0.1625));
	c.addPoint(Posn(0, -0.1625));
	c.addPoint(Posn(0, -0.290));
	c.addPoint(Posn(-0.2875, -0.290));
	components.push_back(make_pair("EngineBlock", c));
}
void LightCycle::addLayeredCircles() {
	Posn innerwheelLeft((-1 * CIRCLE_DISTANCE / 2.0f) - 8, CIRCLE_OFFSET_Y);
	Posn innerwheelRight((CIRCLE_DISTANCE / 2.0f) - 8, CIRCLE_OFFSET_Y);
	innerwheelLeft.setCanvas(c_width, c_height);
	innerwheelRight.setCanvas(c_width, c_height);
	Component c1 = addCircle(innerwheelLeft, 0.12f, GL_POLYGON);
	Component c2 = addCircle(innerwheelRight, 0.12f, GL_POLYGON);
	Component c3 = addCircle(innerwheelLeft, 0.10f, GL_POLYGON);
	Component c4 = addCircle(innerwheelRight, 0.10f, GL_POLYGON);
	components.push_back(make_pair("grayLeft", c1));
	components.push_back(make_pair("grayRight", c2));
	components.push_back(make_pair("blackLeft", c3));
	components.push_back(make_pair("blackRight", c4));
}
void LightCycle::addBottomDetails() {
	Posn start(-0.5625, -0.3125);
	Posn end(0.565, -0.315);
	start.setCanvas(c_width, c_height);
	end.setCanvas(c_width, c_height);
	Component c1(GL_LINE_STRIP);
	c1.addPoint(Posn(start.getX() + 0.2, -0.312));
	c1.addPoint(Posn(end.getX() - 0.2, -0.312));
	Posn right(208, -300);
	Posn left(-208, -300);
	left.setCanvas(c_width, c_height);
	right.setCanvas(c_width, c_height);
	float rad = 50.0f / 800;
	Component c2 = addPartialCircle(right, rad, 15, 90, true, -1, GL_LINE_STRIP);
	Component c3 = addPartialCircle(left, rad, 90, 165, false, -1, GL_LINE_STRIP);
	components.push_back(make_pair("bottomMiddle", c1));
	components.push_back(make_pair("bottomRight", c2));
	components.push_back(make_pair("bottomLeft", c3));
}
void LightCycle::addBottomBar() {
	Component c(GL_POLYGON);
	c.addPoint(Posn(0.285, -0.285));
	c.addPoint(Posn(0.2975, -0.305));
	c.addPoint(Posn(-0.3175, -0.305));
	c.addPoint(Posn(-0.3175, -0.28));
	components.push_back(make_pair("bottomBar", c));
}
void LightCycle::drawDetails() {
	glLineWidth(1.0);
	glColor3d(31 / 255.0f, 1, 233 / 255.0f);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.0649999, 0.07);
	glVertex2f(0.445, -0.0475);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.1325, 0.005);
	glVertex2f(0.345, -0.0625);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2f(-0.4325, 0.025);
	glVertex2f(-0.59, -0.05);
	glEnd();
}

void LightCycle::drawPart(vector<Component> list, float * color, bool trans) {
	glColor3f(color[0], color[1], color[2]);
	vector <Component>::iterator itr;
	for (itr = list.begin(); itr != list.end(); itr++) {
		glBegin(itr->getType());
		for (unsigned int i = 0; i < itr->points.size(); i++) {
			if (trans) {
				glVertex2d(itr->points[i].getXTransformed(), itr->points[i].getYTransformed());
			}
			else {
				glVertex2d(itr->points[i].getX(), itr->points[i].getY());
			}
		}
		glEnd();
	}
	free(color);
}

void LightCycle::drawFront() {
	float * myColor = makeColor(0.1, 0.1, 0.1);
	vector <Component> list;
	list.push_back(getComponent("Front"));
	drawPart(list, myColor, false);
}
void LightCycle::drawBack() {
	float * myColor = makeColor(0.1, 0.1, 0.1);
	vector <Component> list;
	list.push_back(getComponent("Back"));
	drawPart(list, myColor, false);
}
void LightCycle::drawBottomBar() {
	float * myColor = makeColor(0.1, 0.1, 0.1);
	vector <Component> list;	
	list.push_back(getComponent("bottomBar"));
	drawPart(list, myColor, false);
}
void LightCycle::drawBottomDetails() {
	glLineWidth(5.0);
	float * myColor = makeColor(31 / 255.0f, 1, 233 / 255.0f);
	vector <Component> list;
	list.push_back(getComponent("bottomLeft"));
	list.push_back(getComponent("bottomMiddle"));
	list.push_back(getComponent("bottomRight"));
	drawPart(list, myColor, false);
	glLineWidth(1.0);
}
void LightCycle::drawEngineBlock() {
	float * myColor = makeColor(0.08, 0.08, 0.08);
	vector <Component> list;
	list.push_back(getComponent("EngineBlock"));
	drawPart(list, myColor, false);
}
void LightCycle::drawInnerCircles() {
	float * myColor = makeColor(31 / 255.0f, 1, 233 / 255.0f);
	vector <Component> list;
	list.push_back(getComponent("LeftInnerCircle"));
	list.push_back(getComponent("RightInnerCircle"));
	drawPart(list, myColor, false);

}
void LightCycle::drawLayeredCircles() {
	Component c1 = getComponent("grayLeft");
	Component c2 = getComponent("grayRight");
	Component c3 = getComponent("blackLeft");
	Component c4 = getComponent("blackRight");
	glColor3d(0.1, 0.1, 0.1);
	glBegin(c1.getType());
	for (unsigned int i = 0; i < c1.points.size(); i++) {
		glVertex2d(c1.points[i].getX(), c1.points[i].getY());
	}
	glEnd();
	glBegin(c2.getType());
	for (unsigned int i = 0; i < c2.points.size(); i++) {
		glVertex2d(c2.points[i].getX(), c2.points[i].getY());
	}
	glEnd();
	glColor3d(0, 0, 0);
	glBegin(c3.getType());
	for (unsigned int i = 0; i < c3.points.size(); i++) {
		glVertex2d(c3.points[i].getX(), c3.points[i].getY());
	}
	glEnd();
	glBegin(c4.getType());
	for (unsigned int i = 0; i < c4.points.size(); i++) {
		glVertex2d(c4.points[i].getX(), c4.points[i].getY());
	}
	glEnd();
}