////////////////////////////////////////
//3dgraphic.h
//3d�O���t�B�b�N�Ɋւ��鏔�֐�
////////////////////////////////////////
#ifndef INCLUDE_3DGRAPHIC_H
#define INCLUDE_3DGRAPHIC_H
#include "vector.h"

namespace graphic {
	vector convert(vector);
	void draw();
	bool isinScreen(vector);   //�`��͈͓��ɂ��邩����
	void turnRight(float);   //���̊p�x�����E�ɉ�]
	void turnDown(float);   //���̊p�x�������ɉ�]
	void moveCamera(vector);   //����vector�����ړ�
}

#endif