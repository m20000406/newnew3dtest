/////////////////////////////
//d2d.h
//direct2dに関する諸機能
/////////////////////////////
#ifndef INCLUDE_D2D_H
#define INCLUDE_D2D_H
#pragma comment(lib,"d2d1.lib")
#include <windows.h>
#include <D2D1.h>
#include <string>
#include "vector.h"

namespace d2d {
	bool d2dinit(HWND h);
	void rect();
	void beginpaint();
	void endpaint();
	void finish();
	ID2D1HwndRenderTarget* getTarget();
	void dot(D2D1_POINT_2F,D2D1_COLOR_F);   //指定位置に指定色で点を打つ
	void outputDebugInfs(std::wstring);
}

#endif