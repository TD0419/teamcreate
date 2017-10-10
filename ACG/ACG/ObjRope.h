#pragma once
//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：ロープ
class CObjRope :public CObj
{
public:
	CObjRope(int x, int y); // コンストラクタ
	~CObjRope() {};			// デストラクタ
	void Init();			// イニシャライズ
	void Action();			// アクション
	void Draw();			// ドロー
private:
	float m_px;			// ロープX座標
	float m_py;			// ロープY座標
	float m_vx;			// X軸方向のベクトル
	float m_vy;			// Y軸方向のベクトル
	float m_speed;		// 発射速度
	float m_r;			// ロープの角度	
	bool m_caught_flag; //ロープスイッチに引っかかったかを調べる用

};
