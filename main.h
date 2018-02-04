//////////////////////////////
//main.h
//main.cppのへっだ
//////////////////////////////
#ifndef INCLUDE_MAIN_H
#define INCLUDE_MAIN_H
#include <windows.h>

//timerID
const int TIMER_ID = 50;
//初期化関数
BOOL init(HINSTANCE, int);
void finish();
//ウィンドウプロシャージャWndProc
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//ウィンドウクラス登録
ATOM InitApp(HINSTANCE);
//ウィンドウ作成
BOOL InitInstance(HINSTANCE, int);
//幅、高さ
const int WIDTH = 600;
const int HEIGHT = 900;
//移動
void move();
//移動距離
const float g_velocity = 0.25;
//キーコード
const int g_keycodeA = 65;
const int g_keycodeD = 68;
const int g_keycodeW = 83;
const int g_keycodeS = 87;
const int g_keycodeSpace = 16;
const int g_keycodeShift = 32;

#endif