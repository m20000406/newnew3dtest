#pragma once
class color {   //色保存用のクラス r,g,b,それだけ。
public:
	unsigned char r, g, b;
	color(unsigned char, unsigned char, unsigned char);
	color();
};
bool operator==(color a, color b);
bool operator!=(color a, color b);
