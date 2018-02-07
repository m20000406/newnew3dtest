/////////////////////////////
//d2d.cpp
//direct2d�Ɋւ��鏔�@�\
/////////////////////////////
#include "d2d.h"

PAINTSTRUCT paintstruct;   //rect()�p

namespace d2d {
	bool isLoaded = false;
	ID2D1Factory* g_factory = NULL;   //�t�@�N�g���̏�����
	ID2D1HwndRenderTarget* g_target = NULL;   //�����_�[�^�[�Q�b�g�̏�����
	HWND hwnd;   //�E�B���h�E�n���h���ێ�(���ꂢ���̂�?)
	ID2D1SolidColorBrush* solidBrush;
}

bool d2d::d2dinit(HWND h) {
	if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_factory))) {
		MessageBox(NULL, TEXT("�����_�[�t�@�N�g���̎擾�Ɏ��s"), TEXT("ERROR"), MB_OK);
		return false;
	}
	RECT rect;
	hwnd = h;
	GetClientRect(hwnd, &rect);
	D2D1_SIZE_U size = D2D1::SizeU(static_cast<UINT>(rect.right - rect.left), static_cast<UINT>(rect.bottom - rect.top));
	HRESULT hr = g_factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hwnd, size), &g_target);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("�����_�[�^�[�Q�b�g�̎擾�Ɏ��s"), TEXT("ERROR"), MB_OK);
		return false;
	}
	hr = g_target->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Red), &solidBrush
	);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("�u���V���������s"), TEXT("ERROR"), MB_OK);
		return false;
	}
	isLoaded = true;
	return true;
}

void d2d::rect() {
	if (!isLoaded)return;
	RECT rect;
	GetClientRect(hwnd, &rect);
	g_target->Resize(D2D1::Size(
		static_cast<UINT>(rect.right - rect.left), static_cast<UINT>(rect.bottom - rect.top)));
}   //�T�C�Y�ύX���̊֐�

void d2d::beginpaint() {
	::BeginPaint(hwnd, &paintstruct);
	g_target->BeginDraw();
}

void d2d::endpaint() {
	g_target->EndDraw();
	::EndPaint(hwnd, &paintstruct);
}

void d2d::finish() {
	solidBrush->Release();
	g_factory->Release();
	g_target->Release();
}

ID2D1HwndRenderTarget* d2d::getTarget() {
	return d2d::g_target;
}

void d2d::dot(D2D1_POINT_2F pos, D2D1_COLOR_F color) {
	//�u���V�̐F�̕ύX
	solidBrush->SetColor(color);
	//�_��ł�
	g_target->DrawLine(pos,D2D1::Point2F(pos.x+1,pos.y+1),solidBrush,1);
}
