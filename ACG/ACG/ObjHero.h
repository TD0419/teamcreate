#pragma once

//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

#define SHOT_INTERVAL (50.0f)	//弾を撃つ間隔

//振り子の動きをするときに使うデータ
struct Pendulum
{
	float length;		//振り子の長さ
	float pretend_width;//ふり幅
	float time;			//時間(周期)
	float gravity;		//重力加速度
};

//オブジェクト：主人公
class CObjHero:public CObj
{
public:
	CObjHero(int x, int y,int remaining); 		//コンストラクタ
	~CObjHero() {};					//デストラクタ
	void Init();					//イニシャライズ
	void Action();					//アクション
	void Shot();                //発砲関数
	void RopeThrow();			//Rope スロー関数


	void Draw();					//ドロー
	void Scroll();					//スクロール処理の関数
	void LandingCheck();			//着地できてるかどうかを調べる関数
	bool HitUpCheck(int obj_name);	//指定したオブジェクトの上側と当たっているかしらべる関数

	//アクセサ------------------------------------------
	void SetVecX(float x) { m_vx = x; };							//ベクトルXをセットする
	void SetVecY(float y) { m_vy = y; };							//ベクトルYをセットする
	void SetPosX(float x) { m_px = x; };							//ポジションXをセットする
	void SetPosY(float y) { m_py = y; };							//ポジションYをセットする
	void SetHitDown(bool b) { m_hit_down = b; };					//ヒットダウンをセットする
	void SetLaddersUpdown(int x) { m_ladder_updown = x; };			//はしごの上の状況をセットする
	void SetLaddersAniUpdown(int x) { m_ladder_ani_updown = x; };	//はしごの上ってる状況をセットする
	void SetGravityFlag(bool flag) { m_gravity_flag = flag; }		//主人公に重力を入れるかどうかのフラグ true:入れる false:入れない
	float GetPosX() { return m_px; }								//ポジションXを返す
	float GetPosY() { return m_py; }								//ポジションXを返す
	float GetVecX() { return m_vx; }								//ベクトルXを渡す
	float GetVecY() { return m_vy; }								//ベクトルYを渡す
	float GetPosture() { return m_posture; }						//今の主人公の姿勢を渡す
	bool GetRopeAniCon() { return m_rope_ani_con; }					//ロープのアニメーションが始まっているかどうかを返す
	bool GetRopeDeleteRKey() { return m_rope_delete_r_kye; }		//アニメーション用ロープが消えたかどうかを管理するフラグを渡す
	int GetBlockType() { return m_block_type; }						//下のブロック(踏んでいる)情報を渡す
	int GetLadderUpdown() { return m_ladder_updown; }				//主人公がはしごのどのアニメーション中かを返す

	void HeroGoal() { m_goal_flag = true; m_radius = 0.0f; }		//主人公のゴール処理切り替え関数(ゴールフラグを立てる)

private:
	void CircleDraw(float add_radius,float color[4],int type);		// 死亡時とゴール時用の円を描画する関数

private:
	float m_px;		//X座標
	float m_py;		//Y座標
	float m_vx;		//X軸方向のベクトル
	float m_vy;		//Y軸方向のベクトル
	float m_posture;//姿勢 //右：0.0ｆ　左：1.0ｆ
	float m_r;		//主人公の回転角度
	int m_remaining;//残機管理
	int   m_block_type;//踏んでるブロックの値を保存する
	float m_fall_speed_max;//主人公の落下スピード最大速度
	float m_radius; //主人公が死んだ時、周りから黒くする半径の変数
	bool  m_gravity_flag; // 主人公の重力落下フラグ true:重力あり false:重力なし
	bool  m_goal_flag;	  // ゴールフラグ true:ゴールした false:ゴールしていない		
	float m_mous_x;	    //マウスの位置X
	float m_mous_y;     //マウスの位置Y
	float m_rope_moux;	//Rを押したときのマウスの位置X
	float m_rope_mouy;  //Rを押したときのマウスの位置Y
	Pendulum pendulum_data;	//振り子の動きをするときに使うデータ
	//ーーーー制御系---------
	int	  m_count;				  //制御用のカウンター
	int	  m_before_shot_time;	  //最後に弾を撃った時間を保存する	
	bool  m_bullet_control;       //弾丸発射制御用
	bool  m_rope_control;	      //ロープ発射制御用
	bool  m_rope_ani_con;         //ロープアニメーション制御
	bool  m_rope_delete;          //ロープが消えたかどうか調べる変数
	bool  m_rope_delete_r_kye;    //アニメーション用ロープが消えたかどうかを管理する 
	bool  m_rope_delete_control;  //ロープが消えた時の判定を制御する変数
	bool  m_hero_die_flag;        //主人公が死んだ時の高さを制御するためのフラグ
	//-----------
	//-------Heroが死ぬ系---------
	bool   m_hero_die_water;       //主人公が水にあたったかどうかを調べる変数（死）
	bool   m_hero_die_enemy;	   //主人公が敵にあたったかどうかを調べる変数（死）
	bool   m_hero_die_screen_out;  //主人公が画面外（落ちた時）に行ったかどうか調べる変数（死）（シーン移行用）
	float  m_screen_out;           //主人公が死んだ時のｙ位置を記憶するための変数
	//-----------------
	int m_ladder_updown; //はしごが上っているかどうかを調べる（0、上ってない１、上っている　2、はしごを上りきるとき）
	int m_ladder_ani_updown; //はしごアニメーション管理

	//----------------------アニメーション関係
	int m_ani_time_move;	    //移動アニメーションフレーム動作感覚
	int m_ani_frame_move;	    //移動描画フレーム
	int m_ani_frame_stop_move;  //止まった時の移動描画を調整
	int m_ani_max_time_move;    //移動アニメーション動作間隔最大値

	int m_ani_time_ladders;		//はしごアニメーションフレーム動作感覚
	int m_ani_frame_ladders;	//はしご描画フレーム
	int m_ani_max_time_ladders; //はしごアニメーション動作間隔最大値

	int m_ani_time_rope;	    //ロープアニメーションフレーム動作感覚
	int m_ani_frame_rope;	    //ロープ描画フレーム
	int m_ani_max_time_rope;    //ロープアニメーション動作間隔最大値

	int m_ani_time_water_die;         //主人公が水にあたった時アニメーションフレーム動作感覚
	int m_ani_frame_water_die;        //主人公が水にあたった時主人公描画フレーム
	int m_ani_max_time_water_die;     //主人公が水にあたった時主人公アニメーション動作間隔最大値
	
	int m_ani_time_enemy_die;         //主人公が敵にあたった時アニメーションフレーム動作感覚
	int m_ani_frame_enemy_die;        //主人公が敵にあたった時主人公描画フレーム
	int m_ani_max_time_enemy_die;     //主人公が敵にあたった時主人公アニメーション動作間隔最大値

	//------------------------------------------

	//blockとの衝突確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	// 主人公の状態
	enum HeroState
	{
		Normal,		// 通常
		Die,		// 死亡
		Clear,		// クリア
	};
};