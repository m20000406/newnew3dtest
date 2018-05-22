#include "obj_axis.h"
#include "vector.h"

obj_axis::obj_axis():c(){
	for (int i = 0; i < 3; i++) {
		lines[i] = std::dynamic_pointer_cast<obj_line>(objFactory("obj_line"));
		lines[i]->v1 = vector(0,0,0);
	}
	lines[0]->v2 = vector(100,0,0);
	lines[1]->v2 = vector(0, 100, 0);
	lines[2]->v2 = vector(0,0,100);
	lines[0]->c = color(255,0,0);
	lines[1]->c = color(0,255,0);
	lines[2]->c = color(0, 0, 255);
}

void obj_axis::draw() {
	for (int i = 0; i < 3; i++)lines[i]->draw();
}

void obj_axis::addInf(std::string,std::string,Attr) {};