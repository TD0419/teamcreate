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
	CObjLeverSwich(float x, float y); // コンストラクタ
	~CObjLeverSwich() {};	// デストラクタ
	void Init();	// イニシャライズ
	void Action();	// アクション
	void Draw();	// ドロー

private:
	float m_px;	// レバースイッチX座標
	float m_py; // レバースイッチY座標

	//アニメーション関係
	int m_ani_time;         //アニメーションフレーム動作感覚
	int m_ani_frame;        //描画フレーム
	float m_ani_max_time;   //アニメーション動作間隔最大値
};
