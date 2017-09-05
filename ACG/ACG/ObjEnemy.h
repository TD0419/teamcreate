#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：敵
class CObjEnemy : public CObj
{
public:
	CObjEnemy(int x, int y); 	//コンストラクタ
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
	float m_posture;//姿勢　 右向き1.0f 左向き0.0f
	float m_speed;	//スピード
	//アニメーション関係
	int m_ani_time; //アニメーションフレーム動作感覚
	int m_ani_frame;//描画フレーム
	float m_ani_max_time;   //アニメーション動作間隔最大値

	int	  m_first_x;//最初に生成されたときのマップのXの要素数
	int	  m_first_y;//最初に生成されたときのマップのYの要素数

	//blockとの衝突確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;
};