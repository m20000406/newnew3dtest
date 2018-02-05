/////////////////////////////
//d2d.cpp
//direct2dに関する諸機能
/////////////////////////////
#include "d2d.h"

PAINTSTRUCT paintstruct;   //rect()用

namespace d2d {
	bool isLoaded = false;
	ID2D1Factory* g_factory = NULL;   //ファクトリの初期化
	ID2D1HwndRenderTarget* g_target = NULL;   //レンダーターゲットの初期化
	HWND hwnd;   //ウィンドウハンドル保持(これいいのか?)
	ID2D1SolidColorBrush* brushes[3];
}

bool d2d::d2dinit(HWND h) {
	if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_factory))) {
		MessageBox(NULL, TEXT("レンダーファクトリの取得に失敗"), TEXT("ERROR"), MB_OK);
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
		MessageBox(NULL, TEXT("レンダーターゲットの取得に失敗"), TEXT("ERROR"), MB_OK);
		return false;
	}
	hr = g_target->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Red), &brushes[0]
	);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("ブラシ初期化失敗"), TEXT("ERROR"), MB_OK);
		return false;
	}
	hr = g_target->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Green), &brushes[1]
	);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("ブラシ初期化失敗"), TEXT("ERROR"), MB_OK);
		return false;
	}
	hr = g_target->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Blue), &brushes[2]
	);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("ブラシ初期化失敗"), TEXT("ERROR"), MB_OK);
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
}   //サイズ変更時の関数

void d2d::beginpaint() {
	::BeginPaint(hwnd, &paintstruct);
	g_target->BeginDraw();
}

void d2d::endpaint() {
	g_target->EndDraw();
	::EndPaint(hwnd, &paintstruct);
}

void d2d::finish() {
	for (int i = 0; i < 3; i++)brushes[i]->Release();
	g_factory->Release();
	g_target->Release();
}

ID2D1HwndRenderTarget* d2d::getTarget() {
	return d2d::g_target;
}

void d2d::drawLine(vector p1, vector p2, int b) {
	g_target->DrawLine(D2D1::Point2F(p1.x, p1.y), D2D1::Point2F(p2.x, p2.y), brushes[b], 2, NULL);
}
