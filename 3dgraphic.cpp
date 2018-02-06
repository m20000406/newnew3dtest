////////////////////////////////////////
//3dgraphic.cpp
//3dグラフィックに関する諸関数
////////////////////////////////////////
#include "3dgraphic.h"
#include "d2d.h"
#include <math.h>

const float g_near = 0.1;
const float g_far = 40;   //近・遠平面
vector g_pos(0,0,-10);
vector g_eye(0,0,1);
vector g_right(1,0,0);
vector g_down(0,1,0);
//点の位置v
vector graphic::convert(vector v) {
	vector vec = v - g_pos;
	float k = vec*g_eye;
	if (k != 0)vec = g_near / k*vec;
	float x = vec*g_right;
	float y = vec*g_down;
	return vector(10*x,10*y,k)+vector(300,450,0);
}

bool graphic::isinScreen(vector v) {
	if (v.z < g_near || v.z > g_far)return false;   //z座標がおかしい
	if (v.x < 0 || v.x > 600 || v.y < 0 || v.y > 900)return false;   //x,y座標がおかしい
	return true;
}

void graphic::turnRight(float t){
	vector old = g_eye;
	g_eye = old*cos(t) + g_right*sin(t);
	g_right = -1*old*sin(t) + g_right*cos(t);
}

void graphic::turnDown(float t){
	vector old = g_eye;
	g_eye = old*cos(t) + g_down*cos(t);
	g_down = -1 * old*sin(t) + g_down*cos(t);
}

void graphic::draw() {
	static int r = 20;
	d2d::getTarget()->Clear(D2D1::ColorF(D2D1::ColorF::White));
	vector o = graphic::convert(vector(0, 0, 0));
	if (!graphic::isinScreen(o)) {
		OutputDebugString(TEXT("O is not in screen\n"));
		return;
	}
	vector m = graphic::convert(vector(r, 0, 0));
	if(graphic::isinScreen(m))d2d::drawLine(o, m, 0);
	else OutputDebugString(TEXT("(5,0,0) is not in screen\n"));
	m = graphic::convert(vector(0, r, 0));
	if (graphic::isinScreen(m))d2d::drawLine(o, m, 1);
	else OutputDebugString(TEXT("(0,5,0) is not in screen\n"));
	m = graphic::convert(vector(0, 0, r));
	if (graphic::isinScreen(m))d2d::drawLine(o, m, 2);
	else OutputDebugString(TEXT("(0,0,5) is not in screen\n"));
	OutputDebugString("####################\n");
}

void graphic::moveCamera(vector v) {
	g_pos =g_pos + v;
}