#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：弾丸(敵用)
class CObjEnemyBullet :public CObj
{
public:
	CObjEnemyBullet(float x, float y);				//コンストラクタ（BOSS用主人公の方向へ）
	~CObjEnemyBullet() {};	        //デストラクタ
	void Init();	                //イニシャライズ
	void Action();	                //アクション
	void Draw();	                //ドロー
	
private:
	float m_px;						// 弾丸(敵用)X座標
	float m_py;						// 弾丸(敵用)Y座標
	float m_vx;						// X軸方向のベクトル
	float m_vy;						// Y軸方向のベクトル
	float m_speed;					//弾丸の速度
	float m_r;						//弾丸の角度
	
	bool m_delete_flag;//削除するかどうかのフラグ

	//ブロックとの当たり判定用
	bool m_hit_up;
	bool m_hit_right;
	bool m_hit_left;
	bool m_hit_down;
};