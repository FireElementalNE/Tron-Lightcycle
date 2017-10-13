#include <iostream>
#include <vector>
#include "Posn.h"
#ifndef COMP_CLASS
#define COMP_CLASS
using namespace std;

class Component {
private:
	int type;
public:
	vector <Posn> points;
	Component(int s) {
		type = s;
	}
	Component() {}
	int getType() {
		return type;
	}
	vector <Posn> getPoint() {
		return points;
	}
	void addPoint(Posn p) {
		points.push_back(p);
	}
};
#endif