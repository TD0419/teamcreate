#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：ロープ
class CObjRope :public CObj
{
public:
	CObjRope(float arm_x, float arm_y, float mous_x, float mous_y);		// コンストラクタ
	~CObjRope() {};					              // デストラクタ
	void Init();					              // イニシャライズ
	void Action();					              // アクション
	void Draw();					              // ドロー
	void RopeDraw(float color[]);				  // ロープの描画関数
	void RopeDelete();                            // ロープの消える条件の関数
	bool GetCaughtFlag() { return m_caught_flag; }//ロープスイッチに引っかかったかを調べる用の変数を返す
	bool GetTarzanPointFlag() { return m_tarzan_point_flag; }//ターザンに引っかかったかを調べる用の変数を返す
	float GetPosX() { return m_px; }
	float GetPosY() { return m_py; }
	void SetPosX(float x) { m_px = x; }
	void SetPosY(float y) { m_py = y; }
	void Delete();			//自身消去とヒットボックスの消去を行う関数
private:
	float m_px;			 // ロープX座標
	float m_py;			 // ロープY座標
	float m_hero_arm_x;	 //主人公の腕の位置X
	float m_hero_arm_y;	 //主人公の腕の位置Y
	float m_vx;			 // X軸方向のベクトル
	float m_vy;			 // Y軸方向のベクトル
	float m_moux;        //R押したときのマウスの位置Xを入れる変数
	float m_mouy;        //R押したときのマウスの位置Yを入れる変数
	float m_speed;		 // 発射速度
	float m_r;			 // ロープの角度	
	bool  m_caught_flag; //ロープスイッチに引っかかったかを調べる用
	bool  m_r_key_flag;  //ロープスイッチに引っかかるさいにRキーバグを直すための変数（Rキー押したままだとそのまま消える）
	bool m_tarzan_point_flag;//ターザンポイントに引っかかったかどうかフラグ　true=引っかかっている false=引っかかっていない
	//ブロックとの当たり判定用フラグ
	bool m_hit_left;
	bool m_hit_right;
	bool m_hit_up;
	bool m_hit_down;
};
