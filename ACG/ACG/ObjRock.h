#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：岩
class CObjRock :public CObj
{
public:
	CObjRock(int x, int y); //コンストラクタ
	~CObjRock() {};			//デストラクタ
	void Init();			//イニシャライズ
	void Action();			//アクション
	void Draw();			//ドロー
private:
	float m_px;				//岩X座標
	float m_py;				//岩Y座標

	int m_ani_time; //アニメーションフレーム動作感覚
	int m_ani_frame;//描画フレーム
	float m_ani_max_time;   //アニメーション動作間隔最大値
	bool m_ani_start;//アニメーションの始まってるかどうかをあらわすフラグ
};