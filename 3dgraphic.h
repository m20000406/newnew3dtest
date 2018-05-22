////////////////////////////////////////
//3dgraphic.h
//3dグラフィックに関する諸関数
////////////////////////////////////////
#pragma once
#include "vector.h"
#include "color.h"
#define DEBUG

namespace graphic {
	vector convert(vector);
	void draw();
	bool isinScreen(vector);   //描画範囲内にあるか判定
	void turnRight(float);   //この角度だけ右に回転
	void turnDown(float);   //この角度だけ下に回転
	void moveCamera(vector);   //このvectorだけ移動(引数はキーの番号)
	void init();   //graphic全体の初期化
	void dotMap(vector,color);   //mapに点を打つ
	void drawMap();   //mapの実際の描画
	void drawLine(vector,vector,color);
	void goLeft(float);   //dだけ左にカメラを移動
	void goRight(float);   //右へ移動
	void goUp(float);   //上へ移動(「普通の」↑)
	void goDown(float);   //下へ移動
	void goBack(float);   //後ろへ移動
	void goForward(float);   //前に移動
	void cmChange();   //変換用の行列の更新用関数 移動直後に呼ぶ
	int whereis(vector);   //その点がどのような位置にあるか
	void clearMap();
#ifdef DEBUG
	void outputDebugInfs();
#endif
}