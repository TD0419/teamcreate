
#include "GameL\HitBoxManager.h"
#include "GameHead.h"
#include "ObjHero.h"

void CObjHero::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_posture = 0.0f;			 //右向き0.0f 左向き1.0f
	m_r = 0.0f;
	m_radius = 768.0f;
	m_gravity_flag = true;		// true:重力あり false:重力なし
	m_goal_flag = false;		// true:ゴールした false:ゴールしていない
	m_fall_speed_max = 26.0f;	// 主人公の最大落下スピード

	m_mous_x = 0.0f;            //マウスの位置X
	m_mous_y = 0.0f;		    //マウスの位置X
	m_rope_moux = 0.0f;			//Rを押したときのマウスの位置X
	m_rope_mouy = 0.0f;		    //Rを押したときのマウスの位置Y

	m_count = 0;	//カウンターの初期化
	m_before_shot_time = -50;	//弾の発射時間の初期化（スタート直後に打てるように大きめの負の数で初期化）

	m_bullet_control = true;	//弾丸発射制御用
	m_rope_control = false;		//ロープ発射制御用
	m_rope_ani_con = false;
	m_rope_delete = false;    //ロープが消えたかどうか調べる変数
	m_rope_delete_r_kye = false;//アニメーション用ロープが消えたかどうかを管理する 
	m_hero_die_flag = false;

	m_hero_die_water = false;
	m_hero_die_enemy = false;
	m_screen_out = 0.0f;
	
	m_ladder_updown = 0;
	m_ladder_ani_updown = 0;

	m_ani_max_time_move = 6;	//moveアニメーション間隔幅
	m_ani_time_move = 0;
	m_ani_frame_move = 1;		//move静止フレームを初期にする
	m_rope_delete_control = false;
	m_ani_max_time_ladders = 9; //laddersアニメーション間隔幅 
	m_ani_time_ladders = 0;
	m_ani_frame_ladders = 0;	//ladders静止フレームを初期にする

	m_ani_max_time_rope = 4; //ropeアニメーション間隔幅 
	m_ani_time_rope = 0;
	m_ani_frame_rope = 0;	//rope静止フレームを初期にする

	m_ani_max_time_water_die = 25;         //主人公が水に当たった時アニメーション間隔幅 
	m_ani_time_water_die = 0;
	m_ani_frame_water_die = 0;//主人公が水に当たった時静止フレームを初期にする

	m_ani_max_time_enemy_die = 18;         //主人公が敵に当たった時アニメーション間隔幅 
	m_ani_time_enemy_die = 0;
	m_ani_frame_enemy_die = 0;//主人公が敵に当たった時静止フレームを初期にする

	l_jump = false;

	m_block_type = 0;//主人公のしたのブロック情報
	m_block_type_up = 0;

	//ブロックとの衝突した状態(場所)確認用
	m_hit_up = false;
	m_hit_left = false;
	m_hit_right = false;
	m_hit_down = false;

	pendulum_data.gravity = 0.98f;//重力加速度を設定(本当は9.8にしたいけど計算がおかしいのか早くなる)
	pendulum_data.length = 0.0f;	//振り子の長さ
	pendulum_data.pretend_width = 0.0f;//ふり幅
	pendulum_data.time = 0.0f;//時間(周期)
	pendulum_data.find_value_flag = true;//値を求めるかどうかのフラグNO
	
	//当たり判定
	Hits::SetHitBox(this, m_px, m_py, 46, 112, ELEMENT_PLAYER, OBJ_HERO, 1);
}
