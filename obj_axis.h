#pragma once
#include "object.h"
#include "color.h"
#include <memory>
#include "obj_line.h"

class obj_axis : public IObject {
public:
	obj_axis();
	void draw();
	void addInf(std::string, std::string, Attr);
	color c;   //êF
	std::shared_ptr<obj_line> lines[3];
};