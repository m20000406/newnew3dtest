/////////////////////////////
//main.cpp
//���C���̃\�[�X�t�@�C���B��Ȃ��������Ȃ��Ă��킩��B
//////////////////////////////
#include "main.h"
#include "keyboard.h"
#include "mouse.h"
#include "vector.h"
#include "3dgraphic.h"
#include "d2d.h"

void callback();   //30fps�ŌĂяo�����֐�
HWND g_hwnd;   //�E�B���h�E�n���h��

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst, LPSTR lspCmdLine, int nCmdShow) {
	MSG msg;
	BOOL bRet;

	if (!InitApp(hCurInst))return 0;
	if (!InitInstance(hCurInst, nCmdShow))return 0;   //�E�B���h�E�֘A�̏�����
	d2d::d2dinit(g_hwnd);   //direct2d������
	SetTimer(g_hwnd, TIMER_ID, 33, NULL);   //timer�̃Z�b�g
	mouse::create();
	keyboard::create();
	ShowWindow(g_hwnd, nCmdShow);  // �E�B���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(g_hwnd);          // �E�B���h�E���X�V
	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
		if (bRet == -1)break;
		else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	finish();
	return (int)msg.wParam;
}

BOOL init(HINSTANCE hCurInst, int nCmdShow) {
	if (!InitApp(hCurInst))return FALSE;
	if (!InitInstance(hCurInst, nCmdShow))return FALSE;   //�E�B���h�E�֘A�̏�����
														  //d2d_d2dinit(g_hwnd);   //direct2d������
	return true;
}

void finish() {
	keyboard::destroy();
	mouse::destroy();
	//direct2d�֌W�̉��
	d2d::finish();
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {


	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	case WM_CLOSE: {
		if (KillTimer(hWnd, TIMER_ID) == 0)
			MessageBox(hWnd, TEXT("KillTimer error!"), TEXT("ERROR"), MB_YESNO);
		DestroyWindow(hWnd);
		break;
	}
	case WM_SIZE: {
		d2d::rect();
		break;
	}
	case WM_PAINT: {
		callback();
		break;
	}
	case WM_CREATE: {

		break;
	}
	case WM_KEYDOWN: {
		keyboard::getInstance()->keydown(wp);
		break;
	}
	case WM_TIMER: {
		if (wp == TIMER_ID)InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
	case WM_KEYUP: {
		keyboard::getInstance()->keyup(wp);
		break;
	}
	case WM_LBUTTONDOWN: {
		mouse::getInstance()->lbuttondown(lp);
		break;
	}
	case WM_RBUTTONDOWN: {
		mouse::getInstance()->rbuttondown(lp);
		break;
	}
	case WM_MOUSEMOVE: {
		mouse::getInstance()->mousemove(lp);
		break;
	}
	case WM_LBUTTONUP: {
		mouse::getInstance()->lbuttonup();
		break;
	}
	case WM_RBUTTONUP: {
		mouse::getInstance()->rbuttonup();
		break;
	}
	case WM_ERASEBKGND: {
		return FALSE;
	}
	default: {
		return (DefWindowProc(hWnd, msg, wp, lp));
	}


	}
	return 0;
}

ATOM InitApp(HINSTANCE hInst) {
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);           // �\���̂̃T�C�Y
	wc.style = CS_HREDRAW | CS_VREDRAW;       // �N���X�̃X�^�C��
	wc.lpfnWndProc = WndProc;                 // �v���V�[�W����
	wc.cbClsExtra = 0;                        // �⏕������
	wc.cbWndExtra = 0;                        // �⏕������
	wc.hInstance = hInst;                     // �C���X�^���X
	wc.hIcon = (HICON)LoadImage(              // �A�C�R��
		NULL, MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON, 0, 0,
		LR_DEFAULTSIZE | LR_SHARED);
	wc.hCursor = (HCURSOR)LoadImage(          // �J�[�\��
		NULL, MAKEINTRESOURCE(IDC_ARROW),
		IMAGE_CURSOR, 0, 0,
		LR_DEFAULTSIZE | LR_SHARED);
	wc.hbrBackground =                        // �w�i�u���V
		(HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;                   // ���j���[��
	wc.lpszClassName = "classname";           // �N���X��
	wc.hIconSm = (HICON)LoadImage(            // �������A�C�R��
		NULL, MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON, 0, 0,
		LR_DEFAULTSIZE | LR_SHARED);

	return (RegisterClassEx(&wc));
}

BOOL InitInstance(HINSTANCE hInst, int nCmdShow) {
	//�f�X�N�g�b�v�T�C�Y�̊m��
	HWND dhwnd = GetDesktopWindow();
	RECT rect;
	GetClientRect(dhwnd, &rect);
	HWND hwnd = CreateWindowEx(
		0,                              // �I�v�V�����̃E�B���h�E �X�^�C��
		"classname",                     // �E�B���h�E �N���X
		TEXT("Learn to Program Windows"),    // �E�B���h�E �e�L�X�g
		WS_OVERLAPPEDWINDOW,            // �E�B���h�E �X�^�C��

										// �T�C�Y�ƈʒu
		(rect.right - WIDTH) / 2, (rect.bottom - HEIGHT) / 2, WIDTH, HEIGHT,

		NULL,       // �e�E�B���h�E    
		NULL,       // ���j���[
		hInst,  // �C���X�^���X �n���h��
		NULL        // �ǉ��̃A�v���P�[�V���� �f�[�^
	);
	if (!hwnd)
		return FALSE;
	g_hwnd = hwnd;
	return TRUE;
}

void move() {
	if (keyboard::getInstance()->is(g_keycodeA))graphic::moveCamera(vector(-g_velocity, 0, 0));
	if (keyboard::getInstance()->is(g_keycodeD))graphic::moveCamera(vector(g_velocity, 0, 0));
	if (keyboard::getInstance()->is(g_keycodeSpace))graphic::moveCamera(vector(0, -g_velocity, 0));
	if (keyboard::getInstance()->is(g_keycodeShift))graphic::moveCamera(vector(0, g_velocity, 0));
	if (keyboard::getInstance()->is(g_keycodeS))graphic::moveCamera(vector(0, 0, g_velocity));
	if (keyboard::getInstance()->is(g_keycodeW))graphic::moveCamera(vector(0, 0, -g_velocity));
	if (keyboard::getInstance()->is(g_keycodeUp))graphic::turnDown(-g_vdeg);
	if (keyboard::getInstance()->is(g_keycodeDown))graphic::turnDown(g_vdeg);
	if (keyboard::getInstance()->is(g_keycodeRight))graphic::turnRight(g_vdeg);
	if (keyboard::getInstance()->is(g_keycodeLeft))graphic::turnRight(-g_vdeg);
}

void callback() {
	move();
	d2d::beginpaint();
	graphic::draw();
	d2d::endpaint();
}
