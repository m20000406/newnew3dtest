/////////////////////////////
//mouse.h
//�}�E�X�Ɋւ��鏔�@�\
/////////////////////////////
#pragma once
#include <windows.h>

class mouse {
private:
	static mouse* instance;
	mouse();
	bool r, l;
	POINTS rlast, llast, pos;
public:
	static mouse* getInstance();   //�C���X�^���X�擾
	static void create();   //�C���X�^���X�쐬
	static void destroy();   //�C���X�^���X�폜
	bool isRight();   //�E�N���b�N����Ă��邩
	bool isLeft();   //���N���b�N����Ă��邩
	POINTS rLast();   //�Ō�ɉE�N���b�N�������W
	POINTS lLast();   //�Ō�ɍ��N���b�N�������W
	POINTS position();   //���̃}�E�X�̍��W
	void lbuttondown(LPARAM);
	void rbuttondown(LPARAM);
	void mousemove(LPARAM);
	void lbuttonup();
	void rbuttonup();
};
