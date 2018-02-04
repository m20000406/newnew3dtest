//////////////////////////////
//keyboard.h
//�L�[�{�[�h�̊Ǘ�
//////////////////////////////
#ifndef INCLUDE_KEYBOARD_H
#define INCLUDE_KEYBOARD_H
#include <windows.h>

class keyboard {
private:
	static keyboard* instance;
	keyboard();
	bool map[256];
public:
	static keyboard* getInstance();
	static void create();
	static void destroy();
	bool is(int);   //���̃L�[�͍������Ă��邩?
	void keydown(WPARAM);   //wndproc�p
	void keyup(WPARAM);   //wndproc�p
};

#endif