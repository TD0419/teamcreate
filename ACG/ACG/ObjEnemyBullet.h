#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：弾丸(敵用)
class CObjEnemyBullet :public CObj
{
public:
	CObjEnemyBullet(float x, float y, float angle);  //コンストラクタ
	~CObjEnemyBullet() {};	        //デストラクタ
	void Init();	                //イニシャライズ
	void Action();	                //アクション
	void Draw();	                //ドロー
private:
	float m_bullet_x;	            // 弾丸(敵用)X座標
	float m_bullet_y;	            // 弾丸(敵用)Y座標
	float m_bullet_vx;	            // X軸方向のベクトル
	float m_bullet_vy;	            // Y軸方向のベクトル
	float m_speed;					//速さ
	float m_angle;					//弾丸の角度			

};