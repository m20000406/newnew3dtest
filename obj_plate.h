#pragma once
#include "object.h"
#include "vector.h"
#include "color.h"
#include <vector>

class obj_plate : public IObject {
public:
	void draw();
	void addInf(std::string, std::string, Attr);
	vector head;
	std::vector<vector> points;
	std::vector<bool> isDraw;
	std::vector<std::string> tags;
	color frameColor;
	color plateColor;
};