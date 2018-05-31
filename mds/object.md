# object.h,object.cpp
さまざまなオブジェクトのための基底クラスの定義とファクトリ

# IObject(クラス)
基底クラス

draw(仮想0)
- 描画関数

デストラクタ(仮想)
- デストラクタ。通常とくに何もしない

addInf(仮想0)
- メンバに情報を追加
- typename(std::string) 設定メンバの名前
- data(std::string) 設定メンバの値
- attr(Attr) 属性値

tags(vector<strings>)
- タグの保管ベクター

# objFactory
- インスタンスの作成ファクトリ
- typename(std::string) オブジェクト名
~~~C++
objects.push_back(objFactory("型名"));
~~~

#Attr
std::map<std::string,std::string>の再定義