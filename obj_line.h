#pragma once
#include "object.h"
#include "vector.h"
#include "color.h"

class obj_line : public IObject {
public:
	obj_line();
	void draw();
	void addInf(std::string,std::string,Attr);
	vector v1, v2;   //�[�_
	color c;   //�F
	~obj_line();
};