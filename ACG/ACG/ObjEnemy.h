#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：敵
class CObjEnemy : public CObj
{
public:
	CObjEnemy(float x,float y); 	//コンストラクタ
	~CObjEnemy(){}; //デストラクタ
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー

   /*-----------------------アクセサ-------------------------*/
	float GetX() { return m_x; }    // X位置情報取得関数
	float GetY() { return m_y; }    // Y位置情報取得関数
	float GetVX() { return m_vx; }  // X移動速度取得関数
	float GetVY() { return m_vy; }  // Y移動速度取得関数
	void SetX(float x) { m_x = x; } // X位置変更関数
	void SetY(float y) { m_y = y; } // Y位置変更関数
	void SetVX(float vx) { m_vx = vx; } // X移動速度変更関数
	void SetVY(float vy) { m_vy = vy; } // Y移動速度変更関数
private:
	float m_x;	//敵X座標
	float m_y;	//敵Y座標
	float m_vx;	//敵X軸方向のベクトル
	float m_vy;	//敵Y軸方向のベクトル
	float m_r;  //敵の回転角度
};