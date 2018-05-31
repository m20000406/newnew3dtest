#include "xml.h"
#include "vector.h"
#include "color.h"

vector xml2vector(Attr attr) {
	vector v;
	v.x = std::stof(attr["x"]);
	v.y = std::stof(attr["y"]);
	v.z = std::stof(attr["z"]);
	return v;
}

color xml2color(Attr attr) {
	color c;
	c.r = std::stoi(attr["r"]);
	c.g = std::stoi(attr["g"]);
	c.b = std::stoi(attr["b"]);
	return c;
}