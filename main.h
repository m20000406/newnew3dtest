//////////////////////////////
//main.h
//main.cpp�̂ւ���
//////////////////////////////
#ifndef INCLUDE_MAIN_H
#define INCLUDE_MAIN_H
#include <windows.h>

//timerID
const int TIMER_ID = 50;
//�������֐�
BOOL init(HINSTANCE, int);
void finish();
//�E�B���h�E�v���V���[�W��WndProc
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//�E�B���h�E�N���X�o�^
ATOM InitApp(HINSTANCE);
//�E�B���h�E�쐬
BOOL InitInstance(HINSTANCE, int);
//���A����
const int WIDTH = 600;
const int HEIGHT = 900;
//�ړ�
void move();
//�ړ�����
const float g_velocity = 0.25;
//�L�[�R�[�h
const int g_keycodeA = 65;
const int g_keycodeD = 68;
const int g_keycodeW = 83;
const int g_keycodeS = 87;
const int g_keycodeSpace = 16;
const int g_keycodeShift = 32;

#endif