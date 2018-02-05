////////////////////////////////////////
//3dgraphic.cpp
//3d�O���t�B�b�N�Ɋւ��鏔�֐�
////////////////////////////////////////
#include "3dgraphic.h"
#include "d2d.h"
#include <math.h>

const float g_near = 10;
const float g_far = 20;   //�߁E������
//�_�̈ʒuvec�A�J�����̈ʒupos�A�E��]�p�xt�A������]�p�xp
vector graphic::convert(vector vec,vector pos,float t,float p) {
	//�J���������_�ɕ��s�ړ�
	vector v = vec -pos;
	//x����p��]
	v = vector(v.x,v.y*cos(p)-v.z*sin(p),v.y*sin(p)+v.z*cos(p));
	//z����-t��]
	v = vector(v.x*cos(t)-v.z*sin(t),v.y,v.x*sin(t)+v.z*cos(t));
	if (v.z == 0)return vector::zero+vector(300,450,0);
	else return vector(g_near*v.x / v.z, g_near*v.y / v.z, v.z) + vector(300, 450, 0);
}

bool graphic::isinScreen(vector v) {
	if (v.z < g_near || v.z > g_far)return false;   //z���W����������
	if (v.x < 0 || v.x > 600 || v.y < 0 || v.y > 900)return false;   //x,y���W����������
	return true;
}

void graphic::draw(vector pos,float t,float p) {
	static int r = 20;
	d2d::getTarget()->Clear(D2D1::ColorF(D2D1::ColorF::White));
	vector o = graphic::convert(vector(0, 0, 0),pos, t,p);
	if (!graphic::isinScreen(o)) {
		OutputDebugString(TEXT("O is not in screen\n"));
		return;
	}
	vector m = graphic::convert(vector(r, 0, 0), pos, t,p);
	if(graphic::isinScreen(m))d2d::drawLine(o, m, 0);
	else OutputDebugString(TEXT("(5,0,0) is not in screen\n"));
	m = graphic::convert(vector(0, r, 0), pos,t, p);
	if (graphic::isinScreen(m))d2d::drawLine(o, m, 1);
	else OutputDebugString(TEXT("(0,5,0) is not in screen\n"));
	m = graphic::convert(vector(0, 0, r), pos,t, p);
	if (graphic::isinScreen(m))d2d::drawLine(o, m, 2);
	else OutputDebugString(TEXT("(0,0,5) is not in screen\n"));
	OutputDebugString("####################\n");
}