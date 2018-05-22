////////////////////////////////////////
//3dgraphic.h
//3d�O���t�B�b�N�Ɋւ��鏔�֐�
////////////////////////////////////////
#pragma once
#include "vector.h"
#include "color.h"
#define DEBUG

namespace graphic {
	vector convert(vector);
	void draw();
	bool isinScreen(vector);   //�`��͈͓��ɂ��邩����
	void turnRight(float);   //���̊p�x�����E�ɉ�]
	void turnDown(float);   //���̊p�x�������ɉ�]
	void moveCamera(vector);   //����vector�����ړ�(�����̓L�[�̔ԍ�)
	void init();   //graphic�S�̂̏�����
	void dotMap(vector,color);   //map�ɓ_��ł�
	void drawMap();   //map�̎��ۂ̕`��
	void drawLine(vector,vector,color);
	void goLeft(float);   //d�������ɃJ�������ړ�
	void goRight(float);   //�E�ֈړ�
	void goUp(float);   //��ֈړ�(�u���ʂ́v��)
	void goDown(float);   //���ֈړ�
	void goBack(float);   //���ֈړ�
	void goForward(float);   //�O�Ɉړ�
	void cmChange();   //�ϊ��p�̍s��̍X�V�p�֐� �ړ�����ɌĂ�
	int whereis(vector);   //���̓_���ǂ̂悤�Ȉʒu�ɂ��邩
	void clearMap();
#ifdef DEBUG
	void outputDebugInfs();
#endif
}