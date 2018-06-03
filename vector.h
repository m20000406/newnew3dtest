/////////////////////////////
//vector.h
//ヴェクタ関係の云々
/////////////////////////////
#pragma once

class vector {
public:
	vector(float, float, float);
	vector();
	float x, y, z;
	static vector zero;   //0ベクトル
	float norm();   //自分のノルム
	vector operator+=(vector);
	vector operator-=(vector);
	vector operator*=(float);
	vector operator/=(float);
	float operator*=(vector);
private:
};
vector operator+(vector, vector);
vector operator-(vector, vector);
vector operator*(float, vector);
vector operator*(vector, float);
vector operator/(vector, float);   //vectorの加減乗除
float operator*(vector, vector);   //vectorとvectorの内積
vector normalize(vector);   //ベクトルの正規化
vector convert(vector);   //三次元ベクトルを描画平面に変換(z == -1 -> 描画範囲外)
vector round(vector);   //x,y要素をround