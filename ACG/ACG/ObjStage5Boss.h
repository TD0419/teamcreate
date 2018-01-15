#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"
#include "ObjStage5BossArms.h"
//使用するネームスペース
using namespace GameL;

//描画位置の補正用マクロ--------------------

//胴腕接続電気(左腕部分)の描画位置の補正値
#define ELECTRIC_L_CORRECTION_HEIGHT   (14.0f)		//縦
#define ELECTRIC_L_CORRECTION_WIDTH	 (226.0f)		//横

//胴腕接続電気(右腕部分)の描画位置の補正値
#define ELECTRIC_R_CORRECTION_HEIGHT  (4.0f)		//縦
#define ELECTRIC_R_CORRECTION_WIDTH	 (185.0f)		//横

//眼球の描画位置の補正値
#define EYE_CORRECTION_HEIGHT		 (102.0f)		//縦
#define EYE_CORRECTION_WIDTH	      (64.0f)		//横

//------------------------------------------

//オブジェクト：第五ステージのボス
class CObjStage5Boss :public CObj
{
public:
	CObjStage5Boss(int x, int y);      //コンストラクタ
	~CObjStage5Boss() {};	//デストラクタ
	void Init();	        //イニシャライズ
	void Action();	        //アクション
	void Draw();	        //ドロー

	void LastWallHit();//ラストウォールと当たったときの処理

	//アクセサ
	float GetPosY() { return m_py; }
	float GetPosX() { return m_px; }
	void SetVecX(float x) { m_vx = x; }	
	int GetAttackMode() { return m_attack_mode; }
	bool GetBlockDownFlag() { return m_block_down_flag; }
	void SetArmDownFlagRight() { m_right_arm_down_flag = false; }
	void SetArmDownFlagLeft() { m_left_arm_down_flag = false; }
	bool GetArmDownFlagRight() { return m_right_arm_down_flag; }
	bool GetArmDownFlagLeft() { return m_left_arm_down_flag; }
	bool GetBossDeathFlag() { return m_death_flag; }
	//攻撃4カウンターが300フレーム経過した情報を入れる
	bool GetBlockRetuenFlag() { return m_progress_atk4_count; }
	

private:
	float m_px;	 // 第五ボスX座標
	float m_py;	 // 第五ボスY座標
	float m_vx;  // 第五ボスX軸移動ベクトル
	float m_vy;  // 第五ボスY軸移動ベクトル
	int m_hp;    // 第五ボスのＨＰ

	int m_arm_break_count;//腕が壊れた回数を記録する

	int m_attack3_count;//攻撃パターン3用のカウンター
	bool m_attack3_flag;//攻撃パターン3用のフラグ
	bool m_attack4_flag;//攻撃パターン4用のフラグ
	bool m_block_down_flag;//ブロックを落とすかどうかのフラグ
	float m_attack4_scroll;//攻撃パターン４用のスクロール値
	int m_attack4_count;//攻撃パターン3用のカウンター

	//右アームオブジェクトの情報
	CObjStage5BossArms* m_boos_arm_right;
	//左アームオブジェクトの情報
	CObjStage5BossArms* m_boos_arm_left;

	bool m_death_flag;//死亡フラグ　true=死亡している	false=生きている

	//第五ボスの攻撃モード
	//0:何もしない
	//1:主人公のいる位置を取って上から地面までに当たると死ぬ攻撃を落とす
	//2:打ち出してからランダムな時間経過で拡散弾(15度ほど)になる弾を出す
	//3:ボス自身が動きながら主人公の位置に弾を撃つ(レーザー)
	//4:3地点に縄を引っ掛けるオブジェクトを出現させ、その後地面が落ちる攻撃をする。
	int m_attack_mode;

	int m_time;//攻撃のタイミング管理用

	//腕が落ちているかどうかのフラグ
	bool m_right_arm_down_flag;
	bool m_left_arm_down_flag;

	bool m_lastwall_hit_flag;//ラストウォールとの処理用フラグ
	
	bool m_progress_atk4_count;//攻撃4用のカウンターが120フレーム経過したかどうかを判別するための変数

	int m_ani_frame_death[4];	//描画フレーム(死亡)						詳細はInit関数の中の初期化部分
	int m_ani_time_death[4];	//アニメーションフレーム動作間隔(死亡)		詳細はInit関数の中の初期化部分
	int m_ani_max_time_death[2];//アニメーションフレーム動作間隔最大値(死亡)詳細はInit関数の中の初期化部分

	//ボスの死亡アニメーション処理用関数(アクション用)
	bool ActionDeathAnimation();
	//ボスの死亡アニメーション処理用関数(ドロー用)
	void DrawDeathAnimation();

	//ランダムで値を決める関数
	int GetRandom(int min, int max);
};