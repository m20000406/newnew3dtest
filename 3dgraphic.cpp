////////////////////////////////////////
//3dgraphic.cpp
//3d�O���t�B�b�N�Ɋւ��鏔�֐�
////////////////////////////////////////
#include "3dgraphic.h"
#include "d2d.h"
#include <math.h>

const float g_near = 0.3;
const float g_far = 200;   //�߁E������
vector g_pos(0,0,-10);
vector g_eye(0,0,1);
vector g_right(1,0,0);
vector g_down(0,1,0);
float PI = 3.141592;
float theta = PI / 6;   //����p

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
	d2d::beginpaint();
	static int r = 5;
	graphic::initMap();
	d2d::getTarget()->Clear(D2D1::ColorF(D2D1::ColorF::White));
	vector o = graphic::convert(vector(0, 0, 0));
	if (!graphic::isinScreen(o)) {
		OutputDebugString(TEXT("O is not in screen\n"));
	}
	vector m = graphic::convert(vector(r, 0, 0));
	drawLine(o,m,color(255,0,0),2);
	if(!isinScreen(m)) OutputDebugString(TEXT("(r,0,0) is not in screen\n"));
	m = graphic::convert(vector(0, r, 0));
	drawLine(o,m,color(0,255,0),2);
	if(!graphic::isinScreen(m)) OutputDebugString(TEXT("(0,r,0) is not in screen\n"));
	m = graphic::convert(vector(0, 0, r));
	drawLine(o,m,color(0,0,255),2);
	if(!graphic::isinScreen(m)) OutputDebugString(TEXT("(0,0,r) is not in screen\n"));
	OutputDebugString("####################\n");
	drawMap();
	d2d::endpaint();
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

void inline graphic::dotMap(vector v, color c) {
	int x = static_cast<int>(v.x), y = static_cast<int>(v.y);
	if (x < 0 || x > 600 || y < 0 || y > 900 || v.z < g_near || v.z > g_far)return;
	if (map[x][y].flag) {   //��q������
		if (map[x][y].k < v.z)return;   //����Ɏ��������O�ɂ���
	}
	map[x][y] = mapPixel(v.z,c);
}

void graphic::drawLine(vector v1,vector v2,color c,float w) {   //v1���n�_�Av2���I�_�A�F��c�Ƃ��Đ�������
	if (v1.x != v2.x) {
		float d = (v2.y - v1.y) / (v2.x - v1.x);   //�X��
		for (int x = floorf(v1.x); x <= -floorf(-v2.x);x++) {
			float y0;
			if (d != 0)y0 = d*(x - 0.5 - v2.x) + v2.y - w/2;
			else y0 = d*(x - 0.5 - v2.x) + v2.y - w/2;
			y0 = -floorf(-y0);
			float y2;
			if(d != 0)y2 = d*(x + 0.5 - v2.x) + v2.y + w/2;
			else y2 = d*(x + 0.5 - v2.x) + v2.y + w/2;
			y2 = -floorf(-y2);
			float z = (v2.z - v1.z) / (v2.x - v1.x)*(x - v2.x) + v2.z;
			for (int y = y0; y <= y2; y++)dotMap(vector(x,y,z),c);
		}
	}
	else {
		if (v1.y != v2.y) {
			for (int y = min(v1.y, v2.y); y <= max(v1.y, v2.y); y++) {
				float z = (v2.z - v1.z) / (v2.y - v1.y)*(y - v1.y) + v1.z;
				dotMap(vector(v1.x,y,z),c);
			}
		}
		else {
			dotMap(v1,c);
		}
	}
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