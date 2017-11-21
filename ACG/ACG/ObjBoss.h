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

		void SetVX(float x) { m_vx = x; };	//ベクトルXを取得用
		void SetVY(float y) { m_vy = y; };	//ベクトルYを取得用
		void SetPosX(float x) { m_px = x; };		//ポジションXを取得用
		void SetPosY(float y) { m_py = y; };		//ポジションYを取得用
		void SetPosture(float ps) { m_posture = ps; };//ポジションの向き取得
		void SetHitF(bool wall_hit) { m_wall_hit_flag = wall_hit; }; //壁の左側に当たったときのフラグ

		float GetPosX() { return m_px; }			//ポジションXを返す
		float GetPosY() { return m_py; }			//ポジションYを返す
		
		
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

	bool m_wall_hit_flag;	//ボスが壁に当たったときのフラグ
	int m_ani_time;			//アニメーションフレーム動作感覚
	int m_ani_frame;		//描画フレーム
	float m_ani_max_time;   //アニメーション動作間隔最大値
	bool m_ani_start;		//アニメーションの始まってるかどうかをあらわすフラグ
};
