#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：弾丸(敵用)
class CObjEnemyBullet :public CObj
{
public:
	CObjEnemyBullet(float x, float y, float rad);  //コンストラクタ
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
	float m_r;					//弾丸の角度				
};