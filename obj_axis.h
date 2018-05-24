#pragma once
#include "object.h"
#include "color.h"
#include <memory>

class obj_axis : public IObject {
public:
	obj_axis();
	void draw();
	void addInf(std::string, std::string, Attr);
};