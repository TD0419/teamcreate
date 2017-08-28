#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：弾丸
class CObjBullet :public CObj
{
public:
    CObjBullet(float x,float y,float angle) ;  //コンストラクタ
    ~CObjBullet() {};	            //デストラクタ
    void Init();	                //イニシャライズ
    void Action();	                //アクション
    void Draw();	                //ドロー
private:
    float m_bullet_x;	            // 弾丸X座標
    float m_bullet_y;	            // 弾丸Y座標
    float m_bullet_vx;	            // X軸方向のベクトル
    float m_bullet_vy;	            // Y軸方向のベクトル
	float m_speed;					//速さ
	float m_angle;					//弾丸の角度			

};