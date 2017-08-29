#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：弾丸
class CObjBullet :public CObj
{
public:
    CObjBullet(int x, int y) ;  //コンストラクタ
    ~CObjBullet() {};	            //デストラクタ
    void Init();	                //イニシャライズ
    void Action();	                //アクション
    void Draw();	                //ドロー
private:
    float m_px;	// 弾丸X座標
    float m_py;	// 弾丸Y座標
    float m_vx;	// X軸方向のベクトル
    float m_vy;	// Y軸方向のベクトル
	float m_speed;					//速さ
	float m_angle;					//弾丸の角度			

};