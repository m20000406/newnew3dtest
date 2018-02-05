////////////////////////////////////////
//3dgraphic.h
//3d�O���t�B�b�N�Ɋւ��鏔�֐�
////////////////////////////////////////
#ifndef INCLUDE_3DGRAPHIC_H
#define INCLUDE_3DGRAPHIC_H
#include "vector.h"

namespace graphic {
	vector convert(vector, vector, float,float);
	void draw(vector,float,float);
	bool isinScreen(vector);   //�`��͈͓��ɂ��邩����
}

#endif