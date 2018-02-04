/////////////////////////////
//mouse.h
//マウスに関する諸機能
/////////////////////////////
#pragma once
#include <windows.h>

class mouse {
private:
	static mouse* instance;
	mouse();
	bool r, l;
	POINTS rlast, llast, pos;
public:
	static mouse* getInstance();   //インスタンス取得
	static void create();   //インスタンス作成
	static void destroy();   //インスタンス削除
	bool isRight();   //右クリックされているか
	bool isLeft();   //左クリックされているか
	POINTS rLast();   //最後に右クリックした座標
	POINTS lLast();   //最後に左クリックした座標
	POINTS position();   //今のマウスの座標
	void lbuttondown(LPARAM);
	void rbuttondown(LPARAM);
	void mousemove(LPARAM);
	void lbuttonup();
	void rbuttonup();
};
