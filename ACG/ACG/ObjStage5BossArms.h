#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

#define RIGHT_ARM 1
#define LEFT_ARM 2

//オブジェクト：第五ステージのボスの腕
class CObjStage5BossArms :public CObj
{
public:
	//ステージ5ボスcppからの描画の都合で、xとyの型をintからfloatに変更しています。(描画で細かい値を使いたいため)
	CObjStage5BossArms(float x, float y ,int type);      //コンストラクタ
	~CObjStage5BossArms() {};	//デストラクタ
	void Init();	        //イニシャライズ
	void Action();	        //アクション
	void Draw();	        //ドロー

	//アクセサーーーーー-------------------------------
	void SetVecX(float vx) { m_vx = vx; }//ベクトルXをセットする

	void SetInitPosFlagON() { m_initpos_flag = true; }//初期位置に戻すフラグをオンにする
	void SetPosture(bool posture) { m_input_posture = posture; }//入力姿をセットする　true=開く　false=閉じる

	void ArmDownTimeInit() { m_armdown_time = 0; }//タイムの初期化
	bool GetBlockHit() {return m_block_hit_flag;}//ブロックのヒットフラグを返す
	//---------------------------------------------------------
	
	void DiffusionAttack(int limit_time);		//拡散弾を打つ攻撃
	void MoveShotAttack();//移動しながら弾を撃つ攻撃
	void ArmLowerAttack(float x, bool marker);	//腕を下ろす攻撃(下ろすX位置を求めるとき)
	void ArmLowerAttack();			//腕を下ろす攻撃(最初にブロックが当たるまで腕を下ろし続ける)
	void UpdateInitial();//初期位置を計算する
	void Delete();	//HIT_BOXと自身(腕)を消去する

private:
	float m_px;	 // 第五ボスのアームX座標
	float m_py;	 // 第五ボスのアームY座標
	
	float m_vx;  // 第五ボスのアームX軸移動ベクトル
	float m_vy;  // 第五ボスのアームY軸移動ベクトル

	//腕を下ろすX位置
	float m_arm_lower_marker_px;
	//腕を下ろす位置を示すかどうかのフラグ
	bool m_arm_down_marker;
	//腕を下す攻撃をするか否か　true=攻撃をする	false=攻撃をしない
	//フラグがONになってから最初にブロック(落ちる)に当たるまで下ろし続ける
	bool m_arm_down_attack_flag;

	float m_initial_px;//初期X位置(ボスの横)
	float m_initial_py;//初期Y位置(ボスの横)


	int m_time;			//たいみんぐ管理用
	int m_shot_hit_time;//弾丸が当たったたいみんぐの保存用
	bool m_draw_flag;//描画用のフラグ
	bool m_damage_flag;//ダメージフラグ

	int m_arms_type;	 //第五ボスアームのタイプ(1…ライトアーム  2…レフトアーム)
	int m_armdown_time;//腕を下ろすときの管理用タイム
	int m_arm_hp;    // 第五ボスのアームのＨＰ
	bool m_posture;//姿　true=開いている　false=閉じている
	bool m_input_posture;//入力された姿　true=開いている	false=閉じている

	bool m_ani_flag_claw;//爪の開閉アニメーションフラグ　true=アニメーションをする	false=アニメーションをしない

	bool m_wall_hit_flag;//衝突時の多重判定を防ぐフラグ
	bool m_initpos_flag;//初期位置に戻すかどうかのフラグ
	bool m_block_hit_flag;//落ちるブロックと当たっているかどうかの判定

	int m_ani_frame_claw;//描画フレーム(爪)
	int m_ani_time_claw;	//アニメーションフレーム動作感覚(爪)
	int m_ani_max_time_claw;//アニメーションフレーム動作感覚最大値(爪)

	bool m_left_arm_move;//レフトアームが動いているかどうかを判別する
	bool m_right_arm_move;//ライトアームが動いているかどうかを判別する
	
	bool m_arm_down_flag;//腕が落ちてるかどうかのフラグ
};