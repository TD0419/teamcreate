#pragma once

//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：Water
class CObjWater :public CObj
{
public:
	CObjWater(int x, int y); 	//コンストラクタ
	~CObjWater() {};	//デストラクタ
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	
private:
	float m_px;	//X座標
	float m_py;	//Y座標

	//アニメーション関係
	int m_ani_time; //アニメーションフレーム動作感覚
	int m_ani_frame;//描画フレーム
	float m_ani_max_time;   //アニメーション動作間隔最大値
};