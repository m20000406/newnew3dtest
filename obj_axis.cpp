#include "obj_axis.h"
#include "vector.h"
#include "3dgraphic.h"

obj_axis::obj_axis(){}

void obj_axis::draw() {
	graphic::drawLine(vector(0,0,0),vector(5,0,0),color(255,0,0));
	graphic::drawLine(vector(0,0,0),vector(0,5,0),color(0,255,0));
	graphic::drawLine(vector(0, 0, 0), vector(0, 0, 5), color(0, 0, 255));
}

void obj_axis::addInf(std::string,std::string,Attr) {};