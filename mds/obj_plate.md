# obj_plate.h,obj_plate.cpp
面描画のためのファイル

---

## obj_plate

points(std::vector<vector>)
- 面の点の集合

isDraw(std::vector<bool>)
- isDraw[i] == true ->点iとi+1の間の辺を描画

    false -> 描画しない

draw
- 面の描画。

    面を三角形に分割して描画。点の数をnとして、

    (0,n-1,n-2)->(0,n-2,n-3)->(0,n-3,n-4)->...->(0,2,1)

    最初と最後のみ辺描画の云々で別処理

head
- 面の「表」のヴェクタ

---

## draw
点三つ、辺描画有り無しのbool三つ、辺の色、面の色

- boolで分けてそれぞれの辺を描画
- 色塗り
    - 頂点最少x座標から頂点最大x座標まで_xを変化させて、直線x = _xが辺v0-v1,v1-v2,v2-v0をどのように内分するか求める
    - 内分する点が線分上にあるならばその交点を求め、その二点を結ぶ直線を塗る(drawSub)

---

## xml

~~~xml
<plate>   <!-- 面オブジェクト -->
<point x="0",y="0",z="0",isDraw="true"/>
<point x="10",y="0",z="0",isDraw="true"/>
...
<frameColor r="255",g="0",b="0"/>
<plateColor r="0",g="255",b="0"/>
<head x="0",y="1",z="0"/>
</plate>
~~~

- point...点
    - x,y,z...座標
    - isDraw...次の点と結ぶか結ばないか
- frameColor...辺の色
- plateColor...面の色
- head...「表」のヴェクタ