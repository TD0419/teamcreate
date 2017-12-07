#pragma once

//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：弾丸
class CObjBullet :public CObj
{
public:
    CObjBullet(float x,float y,float r) ;		//コンストラクタ
    ~CObjBullet() {};	            //デストラクタ
    void Init();	                //イニシャライズ
    void Action();	                //アクション
    void Draw();	                //ドロー
private:
    float m_px;		// 弾丸X座標
    float m_py;		// 弾丸Y座標
    float m_vx;		// X軸方向のベクトル
    float m_vy;		// Y軸方向のベクトル
	float m_speed;	// 弾丸の速度
	float m_r;	// 弾丸の角度	
	float m_scroll_x;	//スクロールの値X 
	float m_scroll_y;	// スクロールの値Y
	
	//ブロックとの当たり判定用フラグ
	bool m_hit_left;	
	bool m_hit_right;	
	bool m_hit_up;		
	bool m_hit_down;	
};