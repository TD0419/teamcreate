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

private:
	float m_px;	 // 第五ボスX座標
	float m_py;	 // 第五ボスY座標
	float m_vx;  // 第五ボスX軸移動ベクトル
	float m_vy;  // 第五ボスY軸移動ベクトル
	int m_hp;    // 第五ボスのＨＰ

	int m_attack3_count;//攻撃パターン３用のカウンター
	bool m_attack3_flag;//攻撃パターン3のフラグ

	//右アームオブジェクトの情報
	CObjStage5BossArms* m_boos_arm_right;
	//左アームオブジェクトの情報
	CObjStage5BossArms* m_boos_arm_left;

	//第五ボスの攻撃モード
	//0:何もしない
	//1:主人公のいる位置を取って上から地面までに当たると死ぬ攻撃を落とす
	//2:打ち出してからランダムな時間経過で拡散弾(15度ほど)になる弾を出す
	//3:ボス自身が動きながら主人公の位置に弾を撃つ(レーザー)
	//4:3地点に縄を引っ掛けるオブジェクトを出現させ、その後地面が落ちる攻撃をする。
	int m_attack_mode;
	int m_time;//攻撃のたいみんぐ管理用

	bool m_lastwall_hit_flag;//ラストウォールとの処理用フラグ

	//ランダムで値を決める関数
	int GetRandom(int min, int max);
};