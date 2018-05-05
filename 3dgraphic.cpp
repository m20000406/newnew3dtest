////////////////////////////////////////
//3dgraphic.cpp
//3dグラフィックに関する諸関数
////////////////////////////////////////
#pragma warning(disable:4996)
#include "3dgraphic.h"
#include "d2d.h"
#include <math.h>
#include <string>
#include <boost/format.hpp>
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

graphic::color::color(unsigned char rr, unsigned char gg, unsigned char bb) :r(rr), g(gg), b(bb) { };

bool graphic::operator==(graphic::color a, graphic::color b) {
	return (a.r == b.r && a.g == b.g && a.g == b.g);
}

bool graphic::operator!=(graphic::color a, graphic::color b) {
	return !(a == b);
}

//1マスの保存用
class mapPixel {
public:
	float k;   //深さ
	graphic::color col;   //その点の色
	float alpha;   //透明度
	mapPixel(float kk, graphic::color c) :k(kk), col(c) {
		alpha = (k - g_near) / (g_near - g_far) + 1;
	};
	mapPixel() :k(g_far), col(graphic::color(0, 0, 0)) {};
};

typedef std::pair<float, float> descarts;

//std::map<descarts, mapPixel> map;
mapPixel map[600][900];

//点の位置v
vector graphic::convert(vector v) {
	typedef boost::numeric::ublas::vector<float> fvector;
	fvector V(4);
	V(0) = v.x, V(1) = v.y, V(2) = v.z, V(3) = 1;
	V = prod(M, V);
	::vector vec(V(0) / (V(3) + 1e-8), V(1) / (V(3) + 1e-8),(v-g_pos)*g_eye);
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
	//map.clear();
	for (int x = 0; x < WIDTH; x++)
		for (int y = 0; y < HEIGHT; y++)map[x][y] = mapPixel();
	d2d::clear();
	for (int x = -10 * r; x <= 10 * r; x += r)drawLine(vector(x,-10*r,0),vector(x,10*r,0),color(255,0,0));
	for (int y = -10 * r; y <= 10 * r; y += r)drawLine(vector(-10*r,y,0),vector(10*r,y,0),color(0,255,0));
	OutputDebugString("####################\n");
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

void inline graphic::dotMap(vector v, color c) {
	v = vector((int)round(v.x),(int)round(v.y),v.z);
	if (v.x < 0 || v.x > WIDTH || v.y < 0 || v.y > HEIGHT || v.z < (float)g_near || v.z > (float)g_far)return;   //画面外
	/*if (map.find(std::make_pair(round(v.x),round(v.y))) != map.end()) {
		if(map.find(std::make_pair(round(v.x), round(v.y)))->second.k > v.z)
			map.find(std::make_pair(round(v.x), round(v.y)))->second = mapPixel(v.z,c);
	}
	else
	map.insert(std::make_pair(std::make_pair((int)round(v.x),(int)round(v.y)), mapPixel(v.z, c)));
	*/
	if (map[(int)round(v.x)][(int)round(v.y)].k > v.z)map[(int)round(v.x)][(int)round(v.y)] = mapPixel(v.z,c);

}

//x < 0 →1
//x > WIDTH →10
//y < 0 → 100
//y > HEIGHT → 1000
//z < g_near → 10000
//z > g_far → 100000
int whereis(vector v) {
	int temp = 0;
	if (v.x < 0)temp |= 1;
	else if (v.x > WIDTH)temp |= 2;
	if (v.y < 0)temp |= 4;
	else if (v.y > HEIGHT)temp |= 8;
	if (v.z < g_near)temp |= 16;
	else if (v.z > g_far)temp |= 32;
	return temp;
}

float deconvert(vector v, vector v1, vector v2) {   //返還後のvから無理矢理元座標を割り出す
	v -= vector(WIDTH / 2, HEIGHT / 2, 0);
	v1 -= g_pos;
	v2 -= g_pos;
	using namespace boost::numeric::ublas;
	typedef boost::numeric::ublas::vector<float> fvector;
	typedef matrix<float> fmatrix;
	fmatrix A(3, 3);
	float C = (min(WIDTH, HEIGHT) / 2) / (2 * g_near*tan(theta));
	A(0, 0) = C*g_right.x, A(0, 1) = C*g_right.y, A(0, 2) = C*g_right.z;
	A(1, 0) = C*g_down.x, A(1, 1) = C*g_down.y, A(1, 2) = C*g_down.z;
	A(2, 0) = g_eye.x, A(2, 1) = g_eye.y, A(2, 2) = g_eye.z;
	fvector vec(3);
	vec(0) = v.x, vec(1) = v.y, vec(2) = g_near;
	permutation_matrix<> pm1(A.size1());
	lu_factorize(A, pm1);
	lu_substitute(A, pm1, vec);

	fmatrix B(2, 2);
	B(0, 0) = v2.x - v1.x, B(0, 1) = -vec[0];
	B(1, 0) = v2.y - v1.y, B(1, 1) = -vec[1];
	fvector tk(2);
	tk(0) = -v1.x, tk(1) = -v1.y;
	permutation_matrix<> pm2(B.size1());
	lu_factorize(B, pm2);
	lu_substitute(B, pm2, tk);
	return tk[0];
}

typedef boost::numeric::ublas::matrix<float> fmatrix;
typedef boost::numeric::ublas::vector<float> fvector;   //行列とヴェクタのtypedef

fvector solve2(fmatrix a, fvector b) {   //二元方程式を解く
	fmatrix a_(2, 2);
	a_(0, 0) = a(1, 1), a_(0, 1) = -a(0, 1);
	a_(1, 0) = -a(1, 0), a(1, 1) = a(0, 0);
	return boost::numeric::ublas::prod(b, a_) / (a(0, 0)*a(1, 1) - a(0, 1)*a(1, 0) + 1.0e-8);
}

fvector solve3(fmatrix a, fvector b) {
	fmatrix aa(2, 2);
	aa(0, 0) = a(0, 0)*a(2, 2) - a(2, 0)*a(0, 2);
	aa(0, 1) = a(0, 1)*a(2, 2) - a(2, 1)*a(0, 2);
	aa(1, 0) = a(1, 0)*a(2, 2) - a(2, 0)*a(1, 2);
	aa(1, 1) = a(1, 1)*a(2, 2) - a(2, 1)*a(1, 2);
	fvector bb(2);
	bb(0) = a(2, 2)*b(0) - a(0, 2)*b(2);
	bb(1) = a(2, 2)*b(1) - a(1, 2)*b(2);
	fvector xx(2);
	xx = solve2(aa, bb);
	fvector x(3);
	x(0) = xx(0), x(1) = xx(1);
	x(2) = (b(0) - a(0, 0)*x(0) - a(0, 1)*x(1)) / (a(0, 2 + 1.0e-8));
	return x;
}

bool operator<(std::pair<vector, vector> p1, std::pair<vector, vector> p2) {
	return p1.first.x < p2.first.x;
}

void graphic::drawLine(vector v1, vector v2, color c) {   //v1を始点、v2を終点、色をcとして線を引く
	/*第一案*/
	//if (v1.x > v2.x)drawLine(v2,v1,c);
	//if (v1.x == v2.x)return;
	//for (int x = v1.x; x <= v2.x; x++) {
	//	float t = (x - v1.x) / (v2.x - v1.x);
	//	dotMap(graphic::convert(v1+t*(v2-v1)),c);
	//}
	/*第二案：setで疑似再帰関数*/
	//std::set<std::pair<vector, vector>> set;
	//set.insert(std::pair<vector,vector>(v1,v2));
	//while (set.size() != 0) {
	//	auto e = *(set.begin());
	//	set.erase(set.begin());
	//	vector _v1 = graphic::convert(e.first), _v2 = graphic::convert(e.second);
	//	if ((whereis(_v1)&whereis(_v2)) != 0)continue;
	//	vector vv1 = vector(round(_v1.x), round(_v1.y), _v1.z), 
	//		vv2 = vector(round(_v2.x), round(_v2.y), _v2.z);
	//	if ((vv2.x - vv1.x)*(vv2.x - vv1.x) + (vv2.y - vv1.y)*(vv2.y - vv1.y) <= 2) {
	//		dotMap(vv1,c);
	//		dotMap(vv2,c);
	//	}
	//	else {
	//		set.insert(std::pair<vector,vector>(e.first,(e.first+e.second)/2));
	//		set.insert(std::pair<vector,vector>((e.first+e.second)/2,e.second));
	//	}
	//}
	/*第三案:返還後の(x,y)から無理矢理元の座標を割り出す*/
	//fmatrix a(2, 2);
	//a(0, 0) = 5, a(0, 1) = 7;
	//a(1, 0) = 7, a(1, 1) = -3;
	//fvector b(2);
	//b(0) = 3, b(1) = 17;
	//fvector xx(2);
	//xx = solve2(a, b);
	//vector cv1 = graphic::convert(v1), cv2 = graphic::convert(v2);
	//cv1 = vector(round(cv1.x), round(cv1.y), cv1.z), cv2 = vector(round(cv2.x), round(cv2.y), cv2.z);
	//if (abs(cv2.x - cv1.x) >= abs(cv2.y - cv1.y)) {
	//	if (cv1.x > cv2.x)drawLine(v2, v1, c);
	//	float inc = (cv2.y - cv1.y) / (cv2.x - cv1.x);
	//	float y = inc*(max(0, cv1.x) - cv1.x) + cv1.y;
	//	for (int x = max(0, cv1.x); x <= min(cv2.x, WIDTH); x++) {
	//		float t = deconvert(vector(x, y, 0), v1, v2);
	//		dotMap(graphic::convert(v1 + t*(v2 - v1)), c);
	//		y += inc;
	//	}
	//}
	//else {
	//	if (cv1.y > cv2.y)drawLine(v2, v1, c);
	//	float inc = (cv2.x - cv1.x) / (cv2.y - cv1.y);
	//	float x = inc*(max(0, cv1.y) - cv1.y) + cv1.x;
	//	for (int y = max(0, cv1.y); y <= min(cv2.y, HEIGHT); y++) {
	//		float t = deconvert(vector(x, y, 0), v1, v2);
	//		dotMap(graphic::convert(v1 + t*(v2 - v1)), c);
	//		x += inc;
	//	}
	//}
	/*第四案:z>g_nearとz<g_nearで分ける*/
	std::queue<std::pair<vector, vector>> q;
	q.push(std::make_pair(v1,v2));
	while (q.size() != 0) {
		std::pair<vector, vector> p = q.front();
		q.pop();
		vector _v1 = graphic::convert(p.first), _v2 = graphic::convert(p.second);
		int w1 = whereis(_v1), w2 = whereis(_v2);
		if (w1 == 0 && w2 == 0) {   //まともに描画する場合
			_v1 = vector(round(_v1.x), round(_v1.y), round(_v1.z)),
			_v2 = vector(round(_v2.x),round(_v2.y),round(_v2.z));
			if (_v1.x == _v2.x && _v1.y == _v2.y) {
				dotMap(vector(_v1.x, _v1.y, min(_v1.z, _v2.z)), c);
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
		if ((_v1-_v2).norm() < 1)continue;//幅１未満
		else if ((w1 & w2) != 0)continue;   //共通の範囲(描画範囲外)であったら消去だけして帰る
		else if (w1 != 0 || w2 != 0) {   //どちらも描画範囲内というわけではないなら中点分割
			q.push(std::pair<vector,vector>(p.first,(p.first+p.second)/2));
			q.push(std::pair<vector,vector>((p.first+p.second)/2,p.second));
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
				d2d::changeBrushColor(D2D1::ColorF(map[x][y].col.r,map[x][y].col.g,map[x][y].col.b,map[x][y].alpha));
				d2d::dot(D2D1::Point2F(x,y));
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