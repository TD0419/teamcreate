#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：ロープスイッチ
class CObjRopeSwitch :public CObj
{
public:
    CObjRopeSwitch() {};        //コンストラクタ
    ~CObjRopeSwitch() {};	 //デストラクタ
    void Init();	         //イニシャライズ
    void Action();	         //アクション
    void Draw();	         //ドロー
private:
    float m_RopeSwitch_x;	 // ロープスイッチX座標
    float m_RopeSwitch_y;	 // ロープスイッチY座標


};