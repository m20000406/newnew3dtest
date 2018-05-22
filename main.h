//////////////////////////////
//main.h
//main.cpp�̂ւ���
//////////////////////////////
#pragma once
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
//�ړ�
void move();
//���`�b�N�Ă΂��֐�
void draw();
//�ړ�����
const float g_velocity = 0.25;
//�L�[�R�[�h
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
