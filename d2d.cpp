/////////////////////////////
//d2d.cpp
//direct2dに関する諸機能
/////////////////////////////
#include "d2d.h"
#include "dwrite.h"
#pragma comment(lib,"dwrite.lib")

PAINTSTRUCT paintstruct;   //rect()用

namespace d2d {
	bool isLoaded = false;
	ID2D1Factory* g_factory = NULL;   //ファクトリの初期化
	ID2D1HwndRenderTarget* g_target;//レンダーターゲットの初期化
	HWND hwnd;   //ウィンドウハンドル保持(これいいのか?)
	ID2D1SolidColorBrush* solidBrush,*stringBlackBrush;   //画面描画用、文字描画用
	IDWriteFactory* g_wfactory = NULL;   //dwriteのファクトリ
	IDWriteTextFormat* g_textformat = NULL;   //directWriteのテキストフォーマット
}

bool d2d::d2dinit(HWND h) {
	if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_factory))) {
		MessageBox(NULL, TEXT("レンダーファクトリの取得に失敗"), TEXT("ERROR"), MB_OK);
		return false;
	}
	RECT rect;
	hwnd = h;
	GetClientRect(hwnd, &rect);
	D2D1_SIZE_U size = D2D1::SizeU(static_cast<UINT>(rect.right - rect.left), 
		static_cast<UINT>(rect.bottom - rect.top));
	HRESULT hr = g_factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hwnd, size), &g_target);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("レンダーターゲットの取得に失敗"), TEXT("ERROR"), MB_OK);
		return false;
	}
	hr = g_target->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Red), &solidBrush
	);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("ブラシ初期化失敗"), TEXT("ERROR"), MB_OK);
		return false;
	}
	hr = g_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black),&stringBlackBrush);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("文字描画用ブラシ初期化失敗"), TEXT("ERROR"), MB_OK);
		return false;
	}
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&g_wfactory));
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("DirectWrite初期化失敗"), TEXT("ERROR"),MB_OK);
		return false;
	}
	hr = g_wfactory->CreateTextFormat(L"Meiryo",NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,12,L"",&g_textformat);
	if (FAILED(hr)) {
		MessageBox(NULL,TEXT("テキストフォーマット初期化失敗"),TEXT("ERROR"),MB_OK);
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
	if(solidBrush)solidBrush->Release();
	if(g_factory)g_factory->Release();
	if(g_target)g_target->Release();
}

void d2d::changeBrushColor(D2D1_COLOR_F color){
	//solidBrushの色の変更
	solidBrush->SetColor(color);
}

void d2d::dot(D2D1_POINT_2F pos) {
	//点を打つ
	g_target->DrawLine(pos,D2D1::Point2F(pos.x+1,pos.y+1),solidBrush,1);
}

void d2d::outputDebugInfs(std::wstring str) {
	g_target->DrawText(str.c_str(), str.length(), g_textformat, D2D1::RectF(0,0,600,900)
		,stringBlackBrush,D2D1_DRAW_TEXT_OPTIONS_NONE);
}

void d2d::clear() {
	g_target->Clear(D2D1::ColorF(D2D1::ColorF::White));
}