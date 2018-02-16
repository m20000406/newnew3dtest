////////////////////////////////////////
//3dgraphic.h
//3dグラフィックに関する諸関数
////////////////////////////////////////
#ifndef INCLUDE_3DGRAPHIC_H
#define INCLUDE_3DGRAPHIC_H
#include "vector.h"


namespace graphic {
	class color {   //色保存用のクラス r,g,b,それだけ。
	public:
		unsigned char r, g, b;
		color(unsigned char, unsigned char, unsigned char);
	};
	vector convert(vector);
	void draw();
	bool isinScreen(vector);   //描画範囲内にあるか判定
	void turnRight(float);   //この角度だけ右に回転
	void turnDown(float);   //この角度だけ下に回転
	void moveCamera(vector);   //このvectorだけ移動(引数はキーの番号)
	void initMap();   //Mapの初期化
	void init();   //graphic全体の初期化
	void dotMap(vector,color);   //mapに点を打つ
	void drawMap();   //mapの実際の描画
	void drawLine(vector,vector,color,float);
	void goLeft(float);   //dだけ左にカメラを移動
	void goRight(float);   //右へ移動
	void goUp(float);   //上へ移動(「普通の」↑)
	void goDown(float);   //下へ移動
	void goBack(float);   //後ろへ移動
	void goForward(float);   //前に移動
}
#endif