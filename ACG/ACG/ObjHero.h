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
	float GetX() { return m_x; }
	float GetY() { return m_y; }
	float GetVX() { return m_vx; }
	float GetVY() { return m_vy; }
	void SetX(float x) { m_x = x; }
	void SetY(float y) { m_y = y; }
	void SetVX(float vx) { m_vx = vx; }
	void SetVY(float vy) { m_vy = vy; }
private:
	float m_px;	//X座標
	float m_py;	//Y座標
	float m_vx;	//X軸方向のベクトル
	float m_vy;	//Y軸方向のベクトル

};