////////////////////////////////////////
//3dgraphic.cpp
//3d�O���t�B�b�N�Ɋւ��鏔�֐�
////////////////////////////////////////
#include "3dgraphic.h"
#include "d2d.h"

//�_�̈ʒuvec�A�J�����̈ʒupos�A����straight,�Eright�A����down
vector graphic::convert(vector vec, vector pos, vector straight, vector right, vector down) {
	vector vtemp = vec - pos;
	float k = vtemp*straight;
	if (k < 0)return vector(0, 0, -1);   //z == -1 <==> �����̑��ɂȂ�
	vtemp = alpha / k*vtemp;   //���̒i�K�Ŏs���ʏ�ɂ���
	float s = vtemp*down;   //e_d,e_r�̌W��
	float t = vtemp*right;
	return vector(t, s, 0) + vector(300, 450, 0);
}

void graphic::draw(vector pos, vector eye, vector right, vector down) {
	d2d::getTarget()->Clear(D2D1::ColorF(D2D1::ColorF::White));
	vector o = graphic::convert(vector(0, 0, 0), pos, eye, right, down);
	vector m = graphic::convert(vector(20, 0, 0), pos, eye, right, down);
	d2d::drawLine(o, m, 0);
	m = graphic::convert(vector(0, 20, 0), pos, eye, right, down);
	d2d::drawLine(o, m, 1);
	m = graphic::convert(vector(0, 0, 20), pos, eye, right, down);
	d2d::drawLine(o, m, 2);
}