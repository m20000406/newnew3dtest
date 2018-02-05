////////////////////////////////////////
//3dgraphic.h
//3dグラフィックに関する諸関数
////////////////////////////////////////
#ifndef INCLUDE_3DGRAPHIC_H
#define INCLUDE_3DGRAPHIC_H
#include "vector.h"

namespace graphic {
	vector convert(vector, vector, float,float);
	void draw(vector,float,float);
	bool isinScreen(vector);   //描画範囲内にあるか判定
}

#endif