#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：ロープスイッチ
class CObjRopeSwitch :public CObj
{
public:
    CObjRopeSwitch(int x, int y);       //コンストラクタ
    ~CObjRopeSwitch() {};
	//デストラクタ
    void Init();	         //イニシャライズ
    void Action();	         //アクション
    void Draw();	         //ドロー
private:
    float m_px;	 // ロープスイッチX座標
    float m_py;	 // ロープスイッチY座標


};