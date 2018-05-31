#pragma once
class color {   //色保存用のクラス r,g,b,それだけ。
public:
	int r, g, b;
	color(int, int, int);
	color();
};
bool operator==(color a, color b);
bool operator!=(color a, color b);
