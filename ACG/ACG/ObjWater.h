#pragma once

//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：Water(ギミック)
class CObjWater :public CObj
{
public:
	CObjWater(int x, int y); 	//コンストラクタ
	~CObjWater() {};			//デストラクタ
	void Init();				//イニシャライズ
	void Action();				//アクション
	void Draw();				//ドロー
private:
	float m_px;	//X座標
	float m_py;	//Y座標

	//マップ上の位置（要素数）
	int m_map_x;//X
	int m_map_y;//Y

	//アニメーション関係
	int m_ani_time; //アニメーションフレーム動作感覚
	int m_ani_frame;//描画フレーム
	int m_water_audio_count; // 水の音楽制御用の変数　3.75刻みなのでfloat
	int m_ani_max_time;   //アニメーション動作間隔最大値
	float m_water_gauge; // 水位管理
	bool m_ani_start;//アニメーションの始まってるかどうかをあらわすフラグ
};