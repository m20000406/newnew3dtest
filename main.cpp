#include "main.h"
#include "keyboard.h"
#include "mouse.h"
#include "vector.h"
#include "3dgraphic.h"
#include "d2d.h"
#include "object.h"
#include <vector>

void callback();   //30fps�ŌĂяo�����֐�
HWND g_hwnd;   //�E�B���h�E�n���h��
std::vector<std::shared_ptr<IObject>> objs;   //�I�u�W�F�N�g�̔z��

extern const int WIDTH = 600;   //��
extern const int HEIGHT = 900;   //�c

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst, LPSTR lspCmdLine, int nCmdShow) {
	MSG msg;
	BOOL bRet;

	if (!InitApp(hCurInst))return 0;
	if (!InitInstance(hCurInst, nCmdShow))return 0;   //�E�B���h�E�֘A�̏�����
	
	if (!d2d::d2dinit(g_hwnd)) {//direct2d������
		d2d::finish();
		return FALSE;
	}
	std::shared_ptr<IObject> obj = objFactory("obj_plate");
	Attr attr;
	attr["x"] = "1";
	attr["y"] = "0";
	attr["z"] = "0";
	attr["isDraw"] = "true";
	obj->addInf("point", "", attr);
	attr["x"] = "0.5";
	attr["z"] = "0.866";
	obj->addInf("point", "", attr);
	attr["x"] = "-0.5";
	obj->addInf("point", "", attr);
	attr["x"] = "-1";
	attr["z"] = "0";
	obj->addInf("point", "", attr);
	attr["x"] = "-0.5";
	attr["z"] = "-0.866";
	obj->addInf("point", "", attr);
	attr["x"] = "0.5";
	obj->addInf("point", "", attr);
	attr.clear();
	attr["r"] = "128";
	attr["g"] = "128";
	attr["b"] = "128";
	obj->addInf("frameColor", "", attr);
	obj->addInf("plateColor", "", attr);
	attr.clear();
	attr["x"] = "0";
	attr["y"] = "-1";
	attr["z"] = "0";
	obj->addInf("head", "", attr);
	//std::shared_ptr<IObject> obj = objFactory("obj_axis");
	objs.push_back(obj);
	graphic::init();
	SetTimer(g_hwnd, TIMER_ID, 33, NULL);   //timer�̃Z�b�g
	mouse::create();
	keyboard::create();
	ShowWindow(g_hwnd, nCmdShow);  // �E�B���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(g_hwnd);          // �E�B���h�E��X�V
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
	wc.lpszClassName = (LPCSTR)"classname";           // �N���X��
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
		(LPCSTR)"classname",                     // �E�B���h�E �N���X
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
	if (keyboard::getInstance()->is(g_keycodeA))graphic::goLeft(g_velocity);
	if (keyboard::getInstance()->is(g_keycodeD))graphic::goRight(g_velocity);
	if (keyboard::getInstance()->is(g_keycodeSpace))graphic::goDown(g_velocity);
	if (keyboard::getInstance()->is(g_keycodeShift))graphic::goUp(g_velocity);
	if (keyboard::getInstance()->is(g_keycodeS))graphic::goForward(g_velocity);
	if (keyboard::getInstance()->is(g_keycodeW))graphic::goBack(g_velocity);
	if (keyboard::getInstance()->is(g_keycodeUp))graphic::turnDown(-g_vdeg);
	if (keyboard::getInstance()->is(g_keycodeDown))graphic::turnDown(g_vdeg);
	if (keyboard::getInstance()->is(g_keycodeRight))graphic::turnRight(g_vdeg);
	if (keyboard::getInstance()->is(g_keycodeLeft))graphic::turnRight(-g_vdeg);
}

void callback() {
	move();
	draw();
}



void draw() {
	graphic::cmChange();
	d2d::beginpaint();
	static int r = 5;
	graphic::clearMap();
	d2d::clear();

	graphic::cmChange();
	for (size_t i = 0; i < objs.size(); i++)objs[i]->draw();

	graphic::drawMap();
	d2d::endpaint();
}