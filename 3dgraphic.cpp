////////////////////////////////////////
//3dgraphic.cpp
//3d�O���t�B�b�N�Ɋւ��鏔�֐�
////////////////////////////////////////
#include "3dgraphic.h"
#include "d2d.h"
#include <math.h>

const float g_near = 1;
const float g_far = 100;   //�߁E������
vector g_pos(0,0,-10);
vector g_eye(0,0,1);
vector g_right(1,0,0);
vector g_down(0,1,0);
float PI = 3.141592;
float theta = PI / 3;   //����p

graphic::color::color(unsigned char rr, unsigned char gg, unsigned char bb) :r(rr), g(gg), b(bb) { };

//1�}�X�̕ۑ��p
class mapPixel {
public:
	float k;
	graphic::color col;
	bool flag;   //���������_��`�悷�邩(true -> ����)
	float alpha;   //�����x
	mapPixel(float kk, graphic::color c) :k(kk), col(c) {
		flag = true;
		alpha = (k - g_near) / (g_near - g_far) + 1;
	};
	//�����Ȃ��������̂Ƃ��ɂ͉�ʂɕ`�悵�Ȃ����̂Ƃ��ēo�^
	mapPixel() :k(g_far),col(graphic::color(255,255,255)),flag(false),alpha(0) {
	};
};

mapPixel map[600][900];

//�_�̈ʒuv
vector graphic::convert(vector v) {
	vector vec = v - g_pos;
	float k = vec*g_eye;
	if (k != 0)vec = g_near / k*vec;
	float x = vec*g_right*300/(2*g_near*tan(theta));
	float y = vec*g_down*300/(2*g_near*tan(theta));
	return vector(x,y,k)+vector(300,450,0);
}

bool graphic::isinScreen(vector v) {
	if (v.z < g_near || v.z > g_far)return false;   //z���W����������
	if (v.x < 0 || v.x > 600 || v.y < 0 || v.y > 900)return false;   //x,y���W����������
	return true;
}

void graphic::turnRight(float t){
	vector old = g_eye;
	g_eye = old*cos(t) + g_right*sin(t);
	g_right = -1*old*sin(t) + g_right*cos(t);
}

void graphic::turnDown(float t){
	vector old = g_eye;
	g_eye = old*cos(t) + g_down*sin(t);
	g_down = -1 * old*sin(t) + g_down*cos(t);
}

void graphic::draw() {
	static int r = 5;
	graphic::initMap();
	d2d::getTarget()->Clear(D2D1::ColorF(D2D1::ColorF::White));
	vector o = graphic::convert(vector(0, 0, 0));
	if (!graphic::isinScreen(o)) {
		OutputDebugString(TEXT("O is not in screen\n"));
	}
	dotMap(o, color(0,0,0));
	vector m = graphic::convert(vector(r, 0, 0));
	if (graphic::isinScreen(m))dotMap(m,color(255,0,0));
	else OutputDebugString(TEXT("(r,0,0) is not in screen\n"));
	m = graphic::convert(vector(0, r, 0));
	if (graphic::isinScreen(m))dotMap(m, color(0, 255, 0));
	else OutputDebugString(TEXT("(0,r,0) is not in screen\n"));
	m = graphic::convert(vector(0, 0, r));
	if (graphic::isinScreen(m))dotMap(m, color(0, 0, 255));
	else OutputDebugString(TEXT("(0,0,r) is not in screen\n"));
	OutputDebugString("####################\n");
	drawMap();
}

void graphic::moveCamera(vector v) {
	g_pos =g_pos + v;
}

void graphic::initMap(){
	for (int x = 0; x < 600; x++) {
		for (int y = 0; y < 900; y++) map[x][y] = mapPixel();
	}
}

void graphic::init(){
	graphic::initMap();
}

void graphic::dotMap(vector v, color c) {
	int x = static_cast<int>(v.x), y = static_cast<int>(v.y);
	if (x < 0 || x > 600 || y < 0 || y > 900)return;
	map[x][y] = mapPixel(v.z,c);
}

void graphic::drawMap() {   //map�̎��ۂ̕`��
	for (int x = 0; x < 600; x++) {
		for (int y = 0; y < 900; y++) {
			if (!map[x][y].flag)continue;
			D2D1_COLOR_F col = D2D1::ColorF(map[x][y].col.r,map[x][y].col.g,map[x][y].col.b,map[x][y].alpha);
			d2d::dot(D2D1::Point2F(x, y), col);
		}
	}
}