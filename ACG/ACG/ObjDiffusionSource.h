#pragma once

//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：拡散弾の源
class CObjDiffusionSource :public CObj
{
public:
	CObjDiffusionSource(float x, float y,int limit); 	//コンストラクタ
	~CObjDiffusionSource() {};				//デストラクタ
	void Init();						//イニシャライズ
	void Action();						//アクション
	void Draw();						//ドロー

	//アクセサ
	float GetPosX() { return m_px; }
	float GetPosY() { return m_py; }

private:
	float m_px;			//X座標
	float m_py;			//Y座標
	float m_vy;			//移動ベクトル
	float m_vx;			//移動ベクトル
	int m_limit;		//爆発までの時間
};