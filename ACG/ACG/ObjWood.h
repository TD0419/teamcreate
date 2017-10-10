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
	void HeroHit(float px, float py);	//主人公が触れたときの処理
private:
    float m_px;		//木X座標
    float m_py;		//木Y座標
	float m_r;		//回転角度
};
