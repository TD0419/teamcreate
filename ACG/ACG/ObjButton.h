#pragma once
//使用ヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：リフト
class CObjButton : public CObj
{
	public:
		CObjButton(float x, float y);
		~CObjButton() {};
		void Init();	//イニシャライズ
		void Action();  //アクション
		void Draw();	//ドロー

		bool GetFlag() { return m_door_flag; } //弾とあたっているかどうかを返す

	private:
		float m_x;		//位置
		float m_y;

		bool m_door_flag; //弾とあっているかどうかを入れる変数

						  //boolとの衝突状態確認用
		bool m_hit_up;
		bool m_hit_down;
		bool m_hit_left;
		bool m_hit_right;

		int m_ani_time;		//アニメーションフレーム動作間隔
		int m_ani_frame;	//描画フレーム
		int m_ani_max_time;	//アニメーションフレーム動作間隔の最大値
		int m_ani_max_frame;//描画フレームの最大値

};