//////////////////////////////
//keyboard.h
//キーボードの管理
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
	bool is(int);   //そのキーは今押しているか?
	void keydown(WPARAM);   //wndproc用
	void keyup(WPARAM);   //wndproc用
};

#endif