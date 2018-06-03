/**
 * @brief d2d.h/direct2d関係のh
 * 
 * @file d2d.h
 * @author your name
 * @date 2018-05-29
 */
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
	void dot(D2D1_POINT_2F);   //�w��ʒu�Ɏw��F�œ_��ł�
	void outputDebugInfs(std::wstring);
	void clear();
	void changeBrushColor(D2D1_COLOR_F);   //solidBrush�̂����A��
}

//���A����(�͂����Ă����ɏ����͓̂K�؂�?)
//const int WIDTH = 600;
//const int HEIGHT = 900;
const float PI = 3.141592f;
const float g_vdeg = PI / 60;
