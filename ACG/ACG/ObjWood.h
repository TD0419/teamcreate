#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：木(ギミック)
class CObjWood :public CObj
{
public:
    CObjWood(int x, int y);     //コンストラクタ
    ~CObjWood() {};				//デストラクタ
    void Init();				//イニシャライズ
    void Action();				//アクション
    void Draw();				//ドロー
private:
    float m_px;	   // 木X座標
    float m_py;	   // 木Y座標
	float v_px;    // 木の移動量X
	float v_py;    // 木の移動量Y
	float m_r;     // 木を回転させる変数
   

};
