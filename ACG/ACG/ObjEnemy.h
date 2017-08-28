#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：主人公
class CObjEnemy : public CObj
{
public:
	CObjEnemy(int x,int y); 	//コンストラクタ
	~CObjEnemy(){}; //デストラクタ
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー

   /*-----------------------アクセサ-------------------------*/
	float GetX() { return m_enemy_x; }    // X位置情報取得関数
	float GetY() { return m_enemy_y; }    // Y位置情報取得関数
	float GetVX() { return m_enemy_vx; }  // X移動速度取得関数
	float GetVY() { return m_enemy_vy; }  // Y移動速度取得関数
	void SetX(float x) { m_enemy_x = x; } // X位置変更関数
	void SetY(float y) { m_enemy_y = y; } // Y位置変更関数
	void SetVX(float vx) { m_enemy_vx = vx; } // X移動速度変更関数
	void SetVY(float vy) { m_enemy_vy = vy; } // Y移動速度変更関数
private:
	float m_enemy_x;	//敵X座標
	float m_enemy_y;	//敵Y座標
	float m_enemy_vx;	//敵X軸方向のベクトル
	float m_enemy_vy;	//敵Y軸方向のベクトル

};