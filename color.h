#pragma once
class color {   //�F�ۑ��p�̃N���X r,g,b,���ꂾ���B
public:
	int r, g, b;
	color(int, int, int);
	color();
};
bool operator==(color a, color b);
bool operator!=(color a, color b);
