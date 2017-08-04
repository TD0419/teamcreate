#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：主人公
class CObjEnemy : public CObj
{
public:
	CObjEnemy(); 	//コンストラクタ
	~CObjEnemy(){}; //デストラクタ
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー

   /*-----------------------アクセサ-------------------------*/
	float GetX() { return m_Enemy_x; }    // X位置情報取得関数
	float GetY() { return m_Enemy_y; }    // Y位置情報取得関数
	float GetVX() { return m_Enemy_vx; }  // X移動速度取得関数
	float GetVY() { return m_Enemy_vy; }  // Y移動速度取得関数
	void SetX(float x) { m_Enemy_x = x; } // X位置変更関数
	void SetY(float y) { m_Enemy_y = y; } // Y位置変更関数
	void SetVX(float vx) { m_Enemy_vx = vx; } // X移動速度変更関数
	void SetVY(float vy) { m_Enemy_vy = vy; } // Y移動速度変更関数
private:
	float m_Enemy_x;	//敵X座標
	float m_Enemy_y;	//敵Y座標
	float m_Enemy_vx;	//敵X軸方向のベクトル
	float m_Enemy_vy;	//敵Y軸方向のベクトル

};