#include <iostream>
#include <vector>
#include <string>
#include "Posn.h"
#include "component.h"
using namespace std;

class LightCycle {
private:
	bool debug;
	float c_width;
	float c_height;
public:
	float innerCircleRadius;
	float outerCircleRadius;
	vector <pair<string,Component> > components;
	LightCycle(float w, float h, bool db);
	void drawPart(vector<Component> list, float * color, bool trans);
	float * makeColor(float r, float g, float b);
	Component addDashBoard(Component c);
	Component addTrunk(Component c);
	Component addCircle(Posn coord, float radius, int type);
	Component addInnerCircle(Posn Coord, int type);
	Component addPartialCircle(Posn coord, float radius, int start, int end, bool plus, int lastPosn, Component current);
	void initBike();
	void addInnerCircles();
	void addOuterCircles();
	void addFront();
	void addBack();
	void addBottomBar();
	void addBottomDetails();
	void addLayeredCircles();
	void addEngineBlock();
	void drawBike();
	void drawFront();
	void drawBack();
	void drawBottomBar();
	void drawBottomDetails();
	void drawDetails();
	void drawEngineBlock();
	void drawInnerCircles();
	void drawLayeredCircles();
	Component getComponent(string target);
};