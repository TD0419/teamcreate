#pragma once

//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：主人公
class CObjHero:public CObj
{
public:
	CObjHero(int x, int y,int remaining); 		//コンストラクタ
	~CObjHero() {};					//デストラクタ
	void Init();					//イニシャライズ
	void Action();					//アクション
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
	void SetLadderJump(int x) { m_ladder_jump=x; };					//はしごの上の状況をセットする
	float GetPosX() { return m_px; }								//ポジションXを返す
	float GetPosY() { return m_py; }								//ポジションXを返す
	float GetVecX() { return m_vx; }								//ベクトルXを渡す
	float GetVecY() { return m_vy; }								//ベクトルYを渡す
	float GetPosture() { return m_posture; }						//今の主人公の姿勢を渡す
	float GetRopeDeleteAniCon() { return m_rope_delete_ani_con; }   //アニメーション用ロープが消えたかどうかを管理する変数を渡す
	int GetBlockType() { return m_block_type; }						//下のブロック(踏んでいる)情報を渡す

private:
	float m_px;		//X座標
	float m_py;		//Y座標
	float m_vx;		//X軸方向のベクトル
	float m_vy;		//Y軸方向のベクトル
	float m_posture;//姿勢 //右：0.0ｆ　左：1.0ｆ
	float m_r;		//主人公の回転角度
	int   m_block_type;//踏んでるブロックの値を保存する
	int   m_black_radius; //主人公が死んだ時、周りから黒くする半径の変数

	float m_mous_x;	    //マウスの位置X
	float m_mous_y;     //マウスの位置X
	float m_rope_moux;	//Rを押したときのマウスの位置X
	float m_rope_mouy;  //Rを押したときのマウスの位置X
	  
	bool  m_bullet_control;       //弾丸発射制御用
	bool  m_rope_control;	      //ロープ発射制御用
	bool  m_rope_ani_con;         //ロープアニメーション制御
	bool  m_rope_delete;          //ロープが消えたかどうか調べる変数
	bool  m_rope_delete_ani_con;  //アニメーション用ロープが消えたかどうかを管理する 
	bool  m_hero_die_water;       //主人公が水にあたったかどうかを調べる変数（死）
	bool  m_hero_die_enemy;		  //主人公が敵にあたったかどうかを調べる変数（死）

	int m_ladder_updown; //はしごHit管理
	int m_ladder_ani_updown; //はしごアニメーション管理
	int m_ladder_jump;			//はしごジャンプ管理

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

	int m_remaining;//残機管理

	//blockとの衝突確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	
};