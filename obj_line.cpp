#include "obj_line.h"
#include <queue>
#include "3dgraphic.h"
#include <tuple>
#include <windows.h>

using namespace graphic;

obj_line::obj_line() :v1(), v2(),c() {}

void obj_line::addInf(std::string infname, std::string content, Attr attr = Attr()) {
	if (infname == "color")c = color(std::stoi(attr[std::string("r")]),std::stoi(attr[std::string("g")]),std::stoi(attr[std::string("b")]));
	else if (infname.compare(0, 5, "point") == 0) {
		vector v = vector(std::stoi(attr[std::string("x")]), std::stoi(attr[std::string("y")]),std::stoi(attr[std::string("z")]));
		if (infname.length() == 6) {
			if (infname[5] == '1')v1 = v;
			else v2 = v;
		}
	}
	else if (infname == "tag")tags.push_back(content);
}

void obj_line::draw() {
	/*ëÊélàƒ:z>g_nearÇ∆z<g_nearÇ≈ï™ÇØÇÈ*/
	std::queue<std::pair<vector, vector>> q;
	q.push(std::make_pair(v1, v2));
	while (q.size() != 0) {
		std::pair<vector, vector> p = q.front();
		q.pop();
		vector _v1 = graphic::convert(p.first), _v2 = graphic::convert(p.second);
		int w1 = whereis(_v1), w2 = whereis(_v2);
		if (w1 == 0 && w2 == 0) {   //Ç‹Ç∆Ç‡Ç…ï`âÊÇ∑ÇÈèÍçá
			_v1 = vector(round(_v1.x), round(_v1.y), round(_v1.z)),
				_v2 = vector(round(_v2.x), round(_v2.y), round(_v2.z));
			if (_v1.x == _v2.x && _v1.y == _v2.y) {
				if(_v1.z < _v2.z)dotMap(vector(_v1.x, _v1.y, _v1.z), c);
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
		if ((_v1 - _v2).norm() < 1)continue;//ïùÇPñ¢ñû
		else if ((w1 & w2) != 0)continue;   //ã§í ÇÃîÕàÕ(ï`âÊîÕàÕäO)Ç≈Ç†Ç¡ÇΩÇÁè¡ãéÇæÇØÇµÇƒãAÇÈ
		else if (w1 != 0 || w2 != 0) {   //Ç«ÇøÇÁÇ‡ï`âÊîÕàÕì‡Ç∆Ç¢Ç§ÇÌÇØÇ≈ÇÕÇ»Ç¢Ç»ÇÁíÜì_ï™äÑ
			q.push(std::pair<vector, vector>(p.first, (p.first + p.second) / 2));
			q.push(std::pair<vector, vector>((p.first + p.second) / 2, p.second));
			continue;
		}
	}

}

obj_line::~obj_line() {
	OutputDebugString("objline was deleted:");
}