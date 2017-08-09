#pragma once
#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：木(ギミック)
class CObjWood :public CObj
{
public:
    CObjWood();        //コンストラクタ
    ~CObjWood() {};	   //デストラクタ
    void Init();	   //イニシャライズ
    void Action();	   //アクション
    void Draw();	   //ドロー
private:
    float m_wood_x;	   // 木X座標
    float m_wood_y;	   // 木Y座標
   

};
