/////////////////////////////
//mouse.cpp
//マウスに関する諸機能
/////////////////////////////
#include "mouse.h"
#include <windows.h>

mouse* mouse::instance = NULL;

mouse::mouse() {
	r = false, l = false;
}

bool mouse::isRight() {
	return r;
}

bool mouse::isLeft() {
	return l;
}

POINTS mouse::rLast() {
	return rlast;
}

POINTS mouse::lLast() {
	return llast;
}

void mouse::lbuttondown(LPARAM lp) {
	l = true;
	llast = MAKEPOINTS(lp);
}

void mouse::rbuttondown(LPARAM lp) {
	r = true;
	rlast = MAKEPOINTS(lp);
}

void mouse::mousemove(LPARAM lp) {
	pos = MAKEPOINTS(lp);
}

void mouse::lbuttonup() {
	l = false;
}

void mouse::rbuttonup() {
	r = false;
}

POINTS mouse::position() {
	return pos;
}

mouse* mouse::getInstance() {
	return instance;
}

void mouse::create() {
	instance = new mouse;
}

void mouse::destroy() {
	delete instance;
	instance = NULL;
}
