#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：岩
class CObjRock :public CObj
{
public:
	CObjRock(float x, float y); 	//コンストラクタ
	~CObjRock() {};	//デストラクタ
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
private:
	float m_Rock_x;	//岩X座標
	float m_Rock_y;	//岩Y座標

	int m_ani_time;		//アニメーションフレーム動作間隔
	int m_ani_frame;	//描画フレーム
	int m_ani_max_time;	//アニメーションフレーム動作間隔の最大値
	int m_ani_max_frame;//描画フレームの最大値

};