#include <iostream>
using namespace std;
#ifndef POSN_CLASS
#define POSN_CLASS
class Posn {
private:
	float x;
	float y;
	float c_width;
	float c_height;
	float offset_x;
	float offset_y;
public:
	Posn() {}
	Posn(float x1, float y1) {
		x = x1;
		y = y1;
	}
	void setCanvas(float w, float h) {
		c_width = w;
		c_height = h;
		offset_x = 1.0f / w;
		offset_y = 1.0f / h;
	}
	float getX() {
		return x;
	}
	float getY() {
		return y;
	}
	void setX(float x1) {
		x = x1;
	}
	void setY(float y1) {
		y = y1;
	}
	float getXTransformed() {
		return x * offset_x;
	}
	float getYTransformed() {
		return y * offset_y;
	}
};
#endif