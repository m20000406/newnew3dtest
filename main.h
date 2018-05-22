//////////////////////////////
//main.h
//main.cppのへっだ
//////////////////////////////
#pragma once
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
//移動
void move();
//毎チック呼ばれる関数
void draw();
//移動距離
const float g_velocity = 0.25;
//キーコード
const int g_keycodeA = 65;
const int g_keycodeD = 68;
const int g_keycodeW = 83;
const int g_keycodeS = 87;
const int g_keycodeSpace = 16;
const int g_keycodeShift = 32;
const int g_keycodeUp = 38;
const int g_keycodeDown = 40;
const int g_keycodeRight = 39;
const int g_keycodeLeft = 37;
