////////////////////////////////////////
//3dgraphic.cpp
//3dグラフィックに関する諸関数
////////////////////////////////////////
#pragma warning(disable:4996)
#include "3dgraphic.h"
#include "d2d.h"
#include <math.h>
#include <string>
#include <map>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <iostream>
#include <queue>

const float g_near = 1;
const float g_far = 50;   //近・遠平面
vector g_pos(0, 0, -10);
vector g_eye(0, 0, 1);
vector g_right(1, 0, 0);
vector g_down(0, 1, 0);
float theta = PI / 4;   //視野角
extern const int WIDTH;
extern const int HEIGHT;
boost::numeric::ublas::matrix<float> M(4, 4);   //convert用行列

//1マスの保存用
class mapPixel {
public:
	float k;   //深さ
	color col;   //その点の色
	float alpha;   //透明度
	mapPixel(float kk, color c) :k(kk), col(c) {
		alpha = (k - g_near) / (g_near - g_far) + 1;
	};
	mapPixel() :k(g_far), col(color(0, 0, 0)) {};
};

typedef std::pair<float, float> descarts;

//std::map<descarts, mapPixel> map;
mapPixel map[600][900];

//マップ初期化
void graphic::clearMap() {
	for (int x = 0; x < WIDTH; x++)
		for (int y = 0; y < HEIGHT; y++)
			map[x][y] = mapPixel();
}

//点の位置v
vector graphic::convert(vector v) {
	typedef boost::numeric::ublas::vector<float> fvector;
	fvector V(4);
	V(0) = v.x, V(1) = v.y, V(2) = v.z, V(3) = 1;
	V = prod(M, V);
	::vector vec(V(0) / (V(3) + 1e-8), V(1) / (V(3) + 1e-8), (v - g_pos)*g_eye);
	return vec;
}

bool graphic::isinScreen(vector v) {
	if (v.z < g_near || v.z > g_far)return false;   //z座標がおかしい
	if (v.x < 0 || v.x > WIDTH || v.y < 0 || v.y > HEIGHT)return false;   //x,y座標がおかしい
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
	cmChange();
	d2d::beginpaint();
	static int r = 5;
	clearMap();
	d2d::clear();
	for (int x = -10 * r; x <= 10 * r; x += r)drawLine(vector(x, -10 * r, 0), vector(x, 10 * r, 0), color(255, 0, 0));
	for (int y = -10 * r; y <= 10 * r; y += r)drawLine(vector(-10 * r, y, 0), vector(10 * r, y, 0), color(0, 255, 0));
	//drawLine(vector(0, 0, 0), vector(r,0,0),color(255,0,0));
	//drawLine(vector(0,0,0),vector(0,r,0),color(0,255,0));
	//drawLine(vector(0,0,0),vector(0,0,r),color(0,0,255));
	drawMap();
	d2d::endpaint();
}

void graphic::moveCamera(vector v) {
	g_pos = g_pos + v;
}

void graphic::init() {
	//map.clear();
	for (int x = 0; x < WIDTH; x++)
		for (int y = 0; y < HEIGHT; y++)
			map[x][y] = mapPixel();
}

void graphic::dotMap(vector v, color c) {
	v = vector((int)round(v.x), (int)round(v.y), v.z);
	if (v.x < 0 || v.x >= WIDTH || v.y < 0 || v.y >= HEIGHT || v.z < (float)g_near || v.z >(float)g_far)return;   //画面外
	if (map[(int)round(v.x)][(int)round(v.y)].k > v.z)map[(int)round(v.x)][(int)round(v.y)] = mapPixel(v.z, c);

}

//x < 0 -> 1
//x > WIDTH -> 2
//z > g_far -> 4
//0 < z < g_near -> 8
//y < 0 -> 16
//y > HEIGHT -> 32
//z < 0 -> 64
int graphic::whereis(vector v) {
	int temp = 0;
	if (v.z < g_near)return 64;
	if (v.x < 0)temp |= 1;
	else if (v.x > WIDTH)temp |= 2;
	if (v.z > g_far)temp |= 4;
	if (v.y < 0)temp |= 8;
	else if (v.y > HEIGHT)temp |= 16;
	return temp;
}

void graphic::drawLine(vector v1, vector v2, color c) {   //v1を始点、v2を終点、色をcとして線を引く
	/*第四案:z>g_nearとz<g_nearで分ける*/
	std::queue<std::pair<vector, vector>> q;
	q.push(std::make_pair(v1, v2));
	while (q.size() != 0) {
		std::pair<vector, vector> p = q.front();
		q.pop();
		vector _v1 = graphic::convert(p.first), _v2 = graphic::convert(p.second);
		int w1 = whereis(_v1), w2 = whereis(_v2);
		if (w1 == 0 && w2 == 0) {   //まともに描画する場合
			_v1 = vector(round(_v1.x), round(_v1.y), round(_v1.z)),
				_v2 = vector(round(_v2.x), round(_v2.y), round(_v2.z));
			if (_v1.x == _v2.x && _v1.y == _v2.y) {
				if (_v1.z < _v2.z)dotMap(vector(_v1.x, _v1.y, _v1.z), c);
				else dotMap(vector(_v1.x, _v1.y, _v2.z), c);
			}
			else if (_v1.x == _v2.x) {
				if (_v1.y <= _v2.y) {
					vector v = _v1;
					vector t = (_v2 - _v1) / (_v2.y - _v1.y);
					while (v.y <= _v2.y) {
						dotMap(v, c);
						v = v + t;
					}
				}
				else {
					vector v = _v2;
					vector t = (_v1 - _v2) / (_v1.y - _v2.y);
					while (v.y <= _v1.y) {
						dotMap(v, c);
						v = v + t;
					}
				}
			}
			else if (_v1.y == _v2.y) {
				if (_v1.x <= _v2.x) {
					vector v = _v1;
					vector t = (_v2 - _v1) / (_v2.x - _v1.x);
					while (v.x <= _v2.x) {
						dotMap(v, c);
						v = v + t;
					}
				}
				else {
					vector v = _v2;
					vector t = (_v2 - _v1) / (_v2.x - _v1.x);
					while (v.x <= _v2.x) {
						dotMap(v, c);
						v = v + t;
					}
				}
			}
			else if (abs(_v1.x - _v2.x) >= abs(_v1.y - _v2.y)) {
				if (_v1.x <= _v2.x) {
					float t = 1 / (_v2.x - _v1.x + 1.0e-8);
					vector v = _v1;
					while (v.x <= _v2.x) {
						dotMap(v, c);
						v = v + t*(_v2 - _v1);
					}
				}
				else {
					float t = 1 / (_v1.x - _v2.x + 1.0e-8);
					vector v = _v2;
					while (v.x <= _v1.x) {
						dotMap(v, c);
						v = v + t*(_v1 - _v2);
					}
				}
			}
			else {
				if (_v1.y <= _v2.y) {
					float t = 1 / (_v2.y - _v1.y + 1.0e-8);
					vector v = _v1;
					while (v.y <= _v2.y) {
						dotMap(v, c);
						v = v + t*(_v2 - _v1);
					}
				}
				else {
					float t = 1 / (_v1.y - _v2.y + 1.0e-8);
					vector v = _v2;
					while (v.y <= _v1.y) {
						dotMap(v, c);
						v = v + t*(_v1 - _v2);
					}
				}
			}
			continue;
		}
		if ((_v1 - _v2).norm() < 1)continue;//幅１未満
		else if ((w1 & w2) != 0)continue;   //共通の範囲(描画範囲外)であったら消去だけして帰る
		else if (w1 != 0 || w2 != 0) {   //どちらも描画範囲内というわけではないなら中点分割
			q.push(std::pair<vector, vector>(p.first, (p.first + p.second) / 2));
			q.push(std::pair<vector, vector>((p.first + p.second) / 2, p.second));
			continue;
		}
	}
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

void graphic::drawMap() {   //mapの実際の描画
	//for (auto e : map) {
	//	d2d::changeBrushColor(D2D1::ColorF(e.second.col.r,e.second.col.g,e.second.col.b,e.second.alpha));
	//	d2d::dot(D2D1::Point2F(e.first.first,e.first.second));
	//}
	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			if (map[x][y].k != g_far) {
				d2d::changeBrushColor(D2D1::ColorF(map[x][y].col.r, map[x][y].col.g, map[x][y].col.b, map[x][y].alpha));
				d2d::dot(D2D1::Point2F(x, y));
			}
		}
	}
}

//convert用行列の更新用関数
void graphic::cmChange() {
	typedef boost::numeric::ublas::matrix<float> fmatrix;
	//ワールド→平行移動
	fmatrix M0(4, 4);
	M0(0, 0) = 1, M0(0, 1) = 0, M0(0, 2) = 0, M0(0, 3) = -g_pos.x;
	M0(1, 0) = 0, M0(1, 1) = 1, M0(1, 2) = 0, M0(1, 3) = -g_pos.y;
	M0(2, 0) = 0, M0(2, 1) = 0, M0(2, 2) = 1, M0(2, 3) = -g_pos.z;
	M0(3, 0) = 0, M0(3, 1) = 0, M0(3, 2) = 0, M0(3, 3) = 1;
	//平行移動→視線
	fmatrix M1(4, 4);
	M1(0, 0) = g_right.x, M1(0, 1) = g_right.y, M1(0, 2) = g_right.z, M1(0, 3) = 0;
	M1(1, 0) = g_down.x, M1(1, 1) = g_down.y, M1(1, 2) = g_down.z, M1(1, 3) = 0;
	M1(2, 0) = g_eye.x, M1(2, 1) = g_eye.y, M1(2, 2) = g_eye.z, M1(2, 3) = 0;
	M1(3, 0) = 0, M1(3, 1) = 0, M1(3, 2) = 0, M1(3, 3) = 1;
	//視線→画面
	fmatrix M2(4, 4);
	M2(0, 0) = g_near*min(WIDTH, HEIGHT) / 2 / tan(theta), M2(0, 1) = 0, M2(0, 2) = WIDTH / 2, M2(0, 3) = 0;
	M2(1, 0) = 0, M2(1, 1) = g_near*min(WIDTH, HEIGHT) / 2 / tan(theta), M2(1, 2) = HEIGHT / 2, M2(1, 3) = 0;
	M2(2, 0) = 0, M2(2, 1) = 0, M2(2, 2) = g_near, M2(2, 3) = 0;
	M2(3, 0) = 0, M2(3, 1) = 0, M2(3, 2) = 1, M2(3, 3) = 0;
	M = prod(M1, M0);
	M = prod(M2, M);
}