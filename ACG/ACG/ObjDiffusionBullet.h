#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：拡散弾
class CObjDiffusionBullet :public CObj
{
public:
	CObjDiffusionBullet(float x, float y, int r);  //コンストラクタ
	~CObjDiffusionBullet() {};	        //デストラクタ
	void Init();	                //イニシャライズ
	void Action();	                //アクション
	void Draw();	                //ドロー

private:
	float m_px;						// 拡散弾(敵用)X座標
	float m_py;						// 拡散弾(敵用)Y座標
	float m_vx;						// X軸方向のベクトル
	float m_vy;						// Y軸方向のベクトル
	float m_speed;					//拡散弾の速度
	float m_r;					//拡散弾の角度			
	
	//ブロックとの当たり判定用フラグ
	bool m_hit_left;
	bool m_hit_right;
	bool m_hit_up;
	bool m_hit_down;
};