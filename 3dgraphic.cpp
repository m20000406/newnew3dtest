////////////////////////////////////////
//3dgraphic.cpp
//3d�O���t�B�b�N�Ɋւ��鏔�֐�
////////////////////////////////////////
#include "3dgraphic.h"
#include "d2d.h"
#include <math.h>
#include <string>
#include <boost/format.hpp>
#include <map>

const float g_near = 10;
const float g_far = 100;   //�߁E������
vector g_pos(-0.86, -1.25, -11.225);
vector g_eye(0, 0, 1);
vector g_right(1, 0, 0);
vector g_down(0, 1, 0);
float theta = PI / 6;   //����p

graphic::color::color(unsigned char rr, unsigned char gg, unsigned char bb) :r(rr), g(gg), b(bb) { };

bool graphic::operator==(graphic::color a, graphic::color b) {
	return (a.r == b.r && a.g == b.g && a.g == b.g);
}

bool graphic::operator!=(graphic::color a, graphic::color b) {
	return !(a == b);
}

//1�}�X�̕ۑ��p
class mapPixel {
public:
	float k;   //�[��
	graphic::color col;   //���̓_�̐F
	float alpha;   //�����x
	mapPixel(float kk, graphic::color c) :k(kk), col(c) {
		alpha = (k - g_near) / (g_near - g_far) + 1;
	};
};

class descartes {   //map�ō��W���L�[�ɂ���
public:
	int x, y;
	descartes(int _x, int _y) :x(_x), y(_y) {}
};

bool operator<(descartes l, descartes r) {
	if (l.x != r.x)return l.x < r.x;
	return l.y < r.y;
}

std::map<descartes, mapPixel> map;

//�_�̈ʒuv
vector graphic::convert(vector v) {
	vector vec = v - g_pos;
	float k = vec*g_eye;
	if (k == 0)return vector(WIDTH / 2, HEIGHT / 2, 1.0e8);
	vec = g_near / abs(k)*vec;
	float x = vec*g_right * (min(WIDTH,HEIGHT) / 2) / (2 * g_near*tan(theta));
	float y = vec*g_down * (min(WIDTH, HEIGHT) / 2) / (2 * g_near*tan(theta));
	return vector(x, y, k) + vector(WIDTH/2, HEIGHT/2, 0);
}

bool graphic::isinScreen(vector v) {
	if (v.z < g_near || v.z > g_far)return false;   //z���W����������
	if (v.x < 0 || v.x > WIDTH || v.y < 0 || v.y > HEIGHT)return false;   //x,y���W����������
	return true;
}

void graphic::turnRight(float t) {
	vector old = g_eye;
	g_eye = old*cos(t) + g_right*sin(t);
	g_right = -1 * old*sin(t) + g_right*cos(t);
}

void graphic::turnDown(float t) {
	vector old = g_eye;
	g_eye = old*cos(t) + g_down*sin(t);
	g_down = -1 * old*sin(t) + g_down*cos(t);
}

void graphic::draw() {
	d2d::beginpaint();
	static int r = 5;
	map.clear();
	d2d::clear();
	//vector o = graphic::convert(vector(0,0,0));
	//drawLine(o, graphic::convert(vector(10, 0, 0)), color(255,0,0));
	//drawLine(o, graphic::convert(vector(0,10,0)),color(0,255,0));
	//drawLine(o, graphic::convert(vector(0, 0, 10)), color(0, 0, 255));
	for (int x = -10 * r; x <= 10 * r; x += r)
		drawLine(graphic::convert(vector(-10 * r, x, 0)), graphic::convert(vector(10 * r, x, 0)), color(255, 0, 0));
	for (int x = -10 * r; x <= 10 * r; x += r)
		drawLine(graphic::convert(vector(x, -10 * r, 0)), graphic::convert(vector(x, 10 * r, 0)), color(0, 255, 0));
	drawMap();
#ifdef DEBUG
	outputDebugInfs();
#endif
	d2d::endpaint();
}

void graphic::moveCamera(vector v) {
	g_pos = g_pos + v;
}

void graphic::init() {
	map.clear();
}

void inline graphic::dotMap(vector v, color c) {
	if (v.x < 0 || v.x > WIDTH || v.y < 0 || v.y > HEIGHT || v.z < g_near || v.z > g_far)return;   //��ʊO
	auto itr = map.find(descartes(v.x,v.y));   //(v.x,v.y)������
	if (itr != map.end()) {   //���ɒǉ�����Ă���
		if (itr->second.k >= v.z)itr->second = mapPixel(v.z,c);   //�X�V
	}
	else {   //����
		map.insert(std::pair<descartes,mapPixel>(descartes(v.x,v.y),mapPixel(v.z,c)));
	}
}

//x < 0 ��1
//x > WIDTH ��10
//y < 0 �� 100
//y > HEIGHT �� 1000
//z < g_near �� 10000
//z > g_far �� 100000
int whereis(vector v) {
	int temp = 0;
	if (v.x < 0)temp &= 1;
	else if (v.x > WIDTH)temp &= 2;
	if (v.y < 0)temp &= 4;
	else if (v.y > HEIGHT)temp &= 8;
	if (v.z < g_near)temp &= 16;
	else if (v.z > g_far)temp &= 32;
	return temp;
}

void graphic::drawLine(vector v1, vector v2, color c) {   //v1���n�_�Av2���I�_�A�F��c�Ƃ��Đ�������
	v1 = vector(round(v1.x), round(v1.y), v1.z);
	v2 = vector(round(v2.x), round(v2.y), v2.z);   //�����l�ɓ���
	//�ǂ�������ʊO�̕����̂����u�����v�̈�ɑ����Ă����炻�̎��_�ŃA�E�g
	int pv1 = whereis(v1), pv2 = whereis(v2);
	if ((pv1 & pv2) != 0)return;
	if (v1.x > v2.x) {   ///v1�̂ق����E
		drawLine(v2, v1, c);
		return;
	}
	if (v1.x == v2.x && v1.y == v2.y) {   //����̓_
		dotMap(vector(v1.x, v1.y, min(v1.z, v2.z)), c);
		return;
	}
	if (v1.x == v2.x) {
		if (v1.y > v2.y) {   //v1y���W���������Ȃ�悤��
			drawLine(v2, v1, c);
			return;
		}
		float zinc = (v2.z - v1.z) / (v2.y - v1.y);   //y����z�����߂鎞�̌X��("inc"line)
		for (int y = max(0,v1.y); y <= min(HEIGHT,v2.y); y++)
			dotMap(vector(v1.x, y, zinc*(y - v1.y) + v1.z), c);
		return;
	}
	if (v1.y == v2.y) {
		float zinc = (v2.z - v1.z) / (v2.x - v1.x);
		for (int x = max(0,v1.x); x <= min(v2.x,WIDTH); x++)
			dotMap(vector(x, v1.y, zinc*(x - v1.x) + v1.z), c);
		return;
	}
	float inc = (float)((v2.y - v1.y) / (v2.x - v1.x));   //�X��
	int dx = v2.x - v1.x, dy = v2.y - v1.y;   //����x�Ay�Af�Ax���Ay��
	if (dx >= abs(dy)) {
		float y = inc*(max(0, v1.x) - v1.x) + v1.y;   //�ł��n�߂�ŏ��̓_
		float zinc = (v2.z - v1.z) / (v2.x - v1.x);
		for (int x = max(0, v1.x); x <= min(WIDTH, v2.x); x++)
			dotMap(vector(x,inc*(x-v1.x)+v1.y,zinc*(x-v1.x)+v1.z),c);
	}
	else {
		inc = (float)dx / dy;
		float zinc = (v2.z - v1.z) / (v2.y - v1.y);
		for (int y = max(0, min(v1.y,v2.y)); y <= min(HEIGHT, max(v1.y,v2.y)); y++) {
			dotMap(vector(inc*(y-v1.y)+v1.x,y,zinc*(y-v1.y)+v1.z),c);
		}
	}
	return;
}

void graphic::goLeft(float d) {
	g_pos = g_pos - d*g_right;
}

void graphic::goRight(float d) {
	g_pos = g_pos + d*g_right;
}

void graphic::goUp(float d) {
	g_pos = g_pos - d*g_down;
}

void graphic::goDown(float d) {
	g_pos = g_pos + d*g_down;
}

void graphic::goBack(float d) {
	g_pos = g_pos - d*g_eye;
}

void graphic::goForward(float d) {
	g_pos = g_pos + d*g_eye;
}

void graphic::drawMap() {   //map�̎��ۂ̕`��
	color pre = color(255, 255, 255);   //�O�ɓh�����F
	for (auto e : map) {
		mapPixel p = e.second;
		descartes d = e.first;   //Pixel�ƍ��W
		if (p.col != pre) {   //�O�ɓh�����F�Ɣ�r
			D2D1_COLOR_F col =
				D2D1::ColorF(p.col.r,p.col.g,p.col.b,p.alpha);
			d2d::changeBrushColor(col);
			pre = p.col;
		}
		d2d::dot(D2D1::Point2F(d.x,d.y));
	}
}

#ifdef DEBUG
void graphic::outputDebugInfs() {
	using namespace std;
	static int counter = 0;
	string str = (boost::format(
		"position:(%1%,%2%,%3%)\nright degree:%4%\nup degree:%5%")
		% g_pos.x%g_pos.y%g_pos.z % (atan2(g_eye.x, g_eye.z) * 180 / PI) % (atan2(-g_eye.y, g_eye.z) * 180 / PI))
		.str();
	str += (boost::format("\ng_eye:(%1%,%2%,%3%)\ng_right:(%4%,%5%,%6%)\ng_down:(%7%,%8%,%9%)")
		%g_eye.x%g_eye.y%g_eye.z%g_right.x%g_right.y%g_right.z%g_down.x%g_down.y%g_down.z).str();
	str += (boost::format("\ncounter:%1%")%counter).str();
	wstring wstr(L"");
	for (auto c : str) {
		wstr += c;
	}
	d2d::outputDebugInfs(wstr);
	counter++;
}
#endif
