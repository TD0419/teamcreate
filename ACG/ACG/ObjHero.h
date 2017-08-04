#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：主人公
class CObjHero :public CObj
{
public:
	CObjHero(); 	//コンストラクタ
	~CObjHero() {};	//デストラクタ
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー

	/*-----------------------アクセサ-------------------------*/
	float GetX() { return m_Hero_x; }    // X位置情報取得関数
	float GetY() { return m_Hero_y; }    // Y位置情報取得関数
	float GetVX() { return m_Hero_vx; }  // X移動速度取得関数
	float GetVY() { return m_Hero_vy; }  // Y移動速度取得関数
	void SetX(float x) { m_Hero_x = x; } // X位置変更関数
	void SetY(float y) { m_Hero_y = y; } // Y位置変更関数
	void SetVX(float vx) { m_Hero_vx = vx; } // X移動速度変更関数
	void SetVY(float vy) { m_Hero_vy = vy; } // Y移動速度変更関数
private:
	float m_Hero_x;	 //主人公X座標
	float m_Hero_y;	 //主人公Y座標
	float m_Hero_vx; //主人公X軸方向のベクトル
	float m_Hero_vy; //主人公Y軸方向のベクトル

};