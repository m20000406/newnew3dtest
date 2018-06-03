#include "obj_plate.h"
#include "3dgraphic.h"
#include "xml.h"
#include <algorithm>

extern vector g_pos;

//�^����ꂽ�Q�_(����x���W)�̊Ԃ�Fc�œh��
void drawSub(vector v0, vector v1/*�񎟌����W*/,color c) {
	if (v0.y > v1.y) {   //v0��y���W�̂ق����������悤�ɂ��Ă���
		drawSub(v1, v0, c);
		return;
	}
	//���y���W���炻�̓_�̋�Ԃł�z���W��z = a*y+b�ŋ��߂�
	float a = (v1.z - v0.z) / (v1.y-v0.y+1e-8);
	float z = v0.z;
	for (int y = v0.y + 1; y < v1.y; y++) {
		z += a;
		graphic::dotMap(vector(v0.x,y,z),c);
	}
}

void draw(vector v0, vector v1, vector v2, bool b01, bool b12, bool b20, color fc, color pc) {
	//��������
	if (b01)
		graphic::drawLine(v0, v1, fc);
	if (b12)
		graphic::drawLine(v1, v2, fc);
	if (b20)
		graphic::drawLine(v2, v0, fc);
	//�Ƃ肠�����ϊ�
	vector _v0 = graphic::convert(v0), _v1 = graphic::convert(v1),_v2 = graphic::convert(v2);
	//�ʂ̐F��h��
	int x0 = round(std::min(_v0.x,std::min(_v1.x,std::min(_v2.x,(float)600)))),
	x1 = round(std::max(_v0.x, std::max(_v1.x, std::max(_v2.x, (float)0))));
	//�[�_x���W�̂������������́A�傫������
	for (int x = x0; x <= x1; x++) {
		//����x = x�͐���v0-v1��t01:(1-t01)�ɓ���
		float t01 = (x - _v0.x) / (_v1.x - _v0.x);
		float t12 = (x - _v1.x) / (_v2.x - _v1.x);
		float t20 = (x - _v2.x) / (_v0.x - _v2.x);
		if (t01 > 0 && t01 < 1 && t12 > 0 && t12 < 1)
			drawSub((1 - t01)*_v0 + t01*_v1, (1 - t12)*_v1 + t12*_v2, pc);
		if (t12 > 0 && t12 < 1 && t20 > 0 && t20 < 1)
			drawSub((1-t12)*_v1+t12*_v2, (1 - t20)*_v2 + t20*_v0,pc);
		if (t20 > 0 && t20 < 1 && t01 > 0 && t01 < 1)
			drawSub((1-t20)*_v2+t20*_v0, (1 - t01)*_v0 + t01*_v1,pc);

	}
}

void obj_plate::draw() {
	if (g_pos*head < 0)return;   //�ʂ��u���v��������`�悵�Ȃ�
	::draw(points[0], points[points.size()-1], points[points.size()-2], isDraw[points.size() - 1], isDraw[points.size() - 2], false, frameColor, plateColor);
	for (int i = 2; i < points.size() - 2;i++)
		::draw(points[0], points[i + 1], points[i], false, isDraw[i], false, frameColor, plateColor);
	::draw(points[0], points[2], points[1], false, isDraw[1], isDraw[0], frameColor, plateColor);
}

void obj_plate::addInf(std::string type, std::string data, Attr attr) {
	if (type == "point") {
		points.push_back(xml2vector(attr));
		if (attr[std::string("isDraw")] == "true")isDraw.push_back(true);
		else isDraw.push_back(false);
	}
	else if (type == "tag") {
		tags.push_back(data);
	}
	else if (type == "frameColor")
		frameColor = xml2color(attr);
	else if (type == "plateColor")
		plateColor = xml2color(attr);
	else if (type == "head")
		head = xml2vector(attr);
}