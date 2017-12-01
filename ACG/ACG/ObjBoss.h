#pragma once

//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：ボス
class CObjBoss :public CObj
{
	public:
		CObjBoss(int x,int y);  //コンストラクタ
		~CObjBoss() {};			//デストラクタ
		void Init();	        //イニシャライズ
		void Action();	        //アクション
		void Draw();	        //ドロー
		
	private:
		float m_px;		 // ボスX座標
		float m_py;		 // ボスY座標
		float m_vx;		 // ボスX軸方向のベクトル
		float m_vy;		 // ボスY軸方向のベクトル
		float m_posture; // 姿勢 右：0.0f　左：1.0f
		float m_speed;	 // 速度

		int m_hp;		 // ボスのＨＰ

	//blockとの衝突確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	bool m_wall_hit_flag;		//ボスが壁に当たったときのフラグ
	int m_ani_time_walk;		//歩くアニメーションフレーム動作感覚
	int m_ani_time_throw;		//投げるアニメーションフレーム動作感覚
	int m_ani_frame_walk;		//描画フレーム歩く用(歩くモーション)
	int m_ani_frame_throw;		//描画フレーム投げる用(投げるモーション)

	int m_ani_walk_max_time;	//アニメーション歩く動作間隔最大値
	int m_ani_throw_max_time;	//アニメーション投げる動作間隔最大値
	bool m_ani_throw_start_flag;//投げるアニメーション開始フラグ
};
