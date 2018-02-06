////////////////////////////////////////
//3dgraphic.h
//3dグラフィックに関する諸関数
////////////////////////////////////////
#ifndef INCLUDE_3DGRAPHIC_H
#define INCLUDE_3DGRAPHIC_H
#include "vector.h"

namespace graphic {
	vector convert(vector);
	void draw();
	bool isinScreen(vector);   //描画範囲内にあるか判定
	void turnRight(float);   //この角度だけ右に回転
	void turnDown(float);   //この角度だけ下に回転
	void moveCamera(vector);   //このvectorだけ移動
}

#endif