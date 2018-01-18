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
	~CObjEnemy(){};				//デストラクタ
	void Init();				//イニシャライズ
	void Action();				//アクション
	void Draw();				//ドロー

	//アクセサ
	void SetVecX(float vx) { m_vx = vx; } // X移動速度変更関数
	void SetPosture(float posture) { m_posture = posture; }//ポジションセット関数
private:
	float m_px;			//敵X座標
	float m_py;			//敵Y座標
	float m_vx;			//敵X軸方向のベクトル
	float m_vy;			//敵Y軸方向のベクトル
	float m_r;			//敵の回転角度
	float m_posture;	//姿勢　 右向き1.0f 左向き0.0f
	float m_speed;		//移動速度

	//アニメーション関係
	int m_ani_time;			//アニメーションフレーム動作感覚
	int m_ani_frame;		//描画フレーム
	int m_ani_max_time;   //アニメーション動作間隔最大値

	int	  m_map_x;		//最初に生成されたときのマップのXの要素数
	int	  m_map_y;		//最初に生成されたときのマップのYの要素数

	bool m_window_check;//画面内か調べるためのフラグ 画面内:true　画面外:false

	//blockとの衝突確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;
};