////////////////////////////////////////
//3dgraphic.h
//3d�O���t�B�b�N�Ɋւ��鏔�֐�
////////////////////////////////////////
#ifndef INCLUDE_3DGRAPHIC_H
#define INCLUDE_3DGRAPHIC_H
#include "vector.h"


namespace graphic {
	class color {   //�F�ۑ��p�̃N���X r,g,b,���ꂾ���B
	public:
		unsigned char r, g, b;
		color(unsigned char, unsigned char, unsigned char);
	};
	vector convert(vector);
	void draw();
	bool isinScreen(vector);   //�`��͈͓��ɂ��邩����
	void turnRight(float);   //���̊p�x�����E�ɉ�]
	void turnDown(float);   //���̊p�x�������ɉ�]
	void moveCamera(vector);   //����vector�����ړ�(�����̓L�[�̔ԍ�)
	void initMap();   //Map�̏�����
	void init();   //graphic�S�̂̏�����
	void dotMap(vector,color);   //map�ɓ_��ł�
	void drawMap();   //map�̎��ۂ̕`��
	void drawLine(vector,vector,color,float);
	void goLeft(float);   //d�������ɃJ�������ړ�
	void goRight(float);   //�E�ֈړ�
	void goUp(float);   //��ֈړ�(�u���ʂ́v��)
	void goDown(float);   //���ֈړ�
	void goBack(float);   //���ֈړ�
	void goForward(float);   //�O�Ɉړ�
}
#endif