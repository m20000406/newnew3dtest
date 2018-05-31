#include "obj_plate.h"
#include "3dgraphic.h"
#include "xml.h"

extern vector g_pos;

void draw(vector v0, vector v1, vector v2, bool b01, bool b12, bool b20, color fc, color pc) {
	if (b01)
		graphic::drawLine(v0, v1, fc);
	if (b12)
		graphic::drawLine(v1, v2, fc);
	if (b20)
		graphic::drawLine(v2, v0, fc);
}

void obj_plate::draw() {
	if (g_pos*head < 0)return;   //–Ê‚ªu— v‚¾‚Á‚½‚ç•`‰æ‚µ‚È‚¢
	::draw(points[0], points[points.size()-1], points[points.size()-2], isDraw[points.size() - 1], isDraw[points.size() - 2], false, frameColor, plateColor);
	for (int i = 2; i < points.size() - 2;i++)
		::draw(points[0], points[i + 1], points[i], false, isDraw[i], false, frameColor, plateColor);
	::draw(points[0], points[2], points[1], false, isDraw[1], isDraw[0], frameColor, plateColor);
}

void obj_plate::addInf(std::string type, std::string data, Attr attr) {
	if (type == "point") {
		points.push_back(xml2vector(attr));
		if (attr[std::string("isDraw")] == "true")isDraw.push_back(true);
		else isDraw.push_back(false);
	}
	else if (type == "tag") {
		tags.push_back(data);
	}
	else if (type == "frameColor")
		frameColor = xml2color(attr);
	else if (type == "plateColor")
		plateColor = xml2color(attr);
	else if (type == "head")
		head = xml2vector(attr);
}