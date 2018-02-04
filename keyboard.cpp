//////////////////////////////
//keyboard.cpp
//キーボードの管理
//////////////////////////////
#include "keyboard.h"

keyboard* keyboard::instance = NULL;

keyboard::keyboard() {
	for (int i = 0; i < 256; i++)map[i] = false;
}

void keyboard::keydown(WPARAM wp) {
	map[wp] = true;
}

void keyboard::keyup(WPARAM wp) {
	map[wp] = false;
}

bool keyboard::is(int code) {
	return map[code];
}

keyboard* keyboard::getInstance() {
	return instance;
}

void keyboard::create() {
	instance = new keyboard;
	for (int i = 0; i < 256; i++)instance->map[i] = false;
}

void keyboard::destroy() {
	delete instance;
	instance = NULL;
}