#pragma once
#include <string>
#include <memory>
#include <tuple>
#include <map>
#include <vector>

typedef std::map<std::string, std::string> Attr;   //addInfの引数用

//オブジェクトのための仮想クラス
class IObject {
public:
	virtual void draw() = 0;   //描画用関数
	virtual ~IObject() {};   //デストラクタ
	virtual void addInf(std::string, std::string, Attr = Attr() ) = 0;   //情報設定用の関数
	std::vector<std::string> tags;
};

//objectオブジェクトのファクトリ
std::shared_ptr<IObject> objFactory(std::string);