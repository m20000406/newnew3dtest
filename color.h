#pragma once
class color {   //�F�ۑ��p�̃N���X r,g,b,���ꂾ���B
public:
	unsigned char r, g, b;
	color(unsigned char, unsigned char, unsigned char);
	color();
};
bool operator==(color a, color b);
bool operator!=(color a, color b);
