/////////////////////////////
//d2d.h
//direct2dÇ…ä÷Ç∑ÇÈèîã@î\
/////////////////////////////
#ifndef INCLUDE_D2D_H
#define INCLUDE_D2D_H
#pragma comment(lib,"d2d1.lib")
#include <windows.h>
#include <D2D1.h>
#include "vector.h"

namespace d2d {
	bool d2dinit(HWND h);
	void rect();
	void beginpaint();
	void endpaint();
	void finish();
	ID2D1HwndRenderTarget* getTarget();
	void drawLine(vector, vector, int);
}

#endif