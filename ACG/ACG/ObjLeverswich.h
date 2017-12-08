#pragma once
//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：レバースイッチ
class CObjLeverSwich :public CObj
{
public:
	CObjLeverSwich(int x, int y);	// コンストラクタ
	~CObjLeverSwich() {};				// デストラクタ
	void Init();						// イニシャライズ
	void Action();						// アクション
	void Draw();						// ドロー
	bool GetWater() { return m_water_con; } //レバーとスイッチが当たっているかどうかを入れる変数（Water用）
	bool GetWood() { return m_wood_con; } //レバーとスイッチが当たっているかどうかを入れる変数(Wood用)

private:
	float m_px;				// レバースイッチX座標
	float m_py;				// レバースイッチY座標
	bool  m_water_con;      // 水の判定を入れる変数
	bool m_wood_con;		// 木の判定を入れる変数
	bool m_ani_flag;        // アニメーションを連続でさせないフラグ変数
	bool m_ani_flag2;       // アニメーションを連続でさせないフラグ変数の二つ目
	//マップの要素数
	int m_map_x;
	int m_map_y;

	//アニメーション関係
	int m_ani_time;         //アニメーションフレーム動作感覚
	int m_ani_frame;        //描画フレーム
	float m_ani_max_time;   //アニメーション動作間隔最大値
};
