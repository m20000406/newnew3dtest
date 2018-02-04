////////////////////////////////////////
//3dgraphic.cpp
//3dグラフィックに関する諸関数
////////////////////////////////////////
#include "3dgraphic.h"
#include "d2d.h"

//点の位置vec、カメラの位置pos、視線straight,右right、したdown
vector graphic::convert(vector vec, vector pos, vector straight, vector right, vector down) {
	vector vtemp = vec - pos;
	float k = vtemp*straight;
	if (k < 0)return vector(0, 0, -1);   //z == -1 <==> 視線の側にない
	vtemp = alpha / k*vtemp;   //この段階で市平面上にある
	float s = vtemp*down;   //e_d,e_rの係数
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