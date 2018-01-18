#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：ボタン
class CObjButton : public CObj
{
	public:
		CObjButton(int x, int y);	//コンストラクタ
		~CObjButton() {};			//デクトラクタ
		void Init();				//イニシャライズ
		void Action();				//アクション
		void Draw();				//ドロー

		/*-----------------------アクセサ-------------------------*/
		bool GetTrickFlag() { return m_trick_flag; } //弾とあたっているかどうかを返す

	private:
		float m_px;			//ボタンX位置
		float m_py;			//ボタンY位置
		//マップの要素数
		int m_map_x;
		int m_map_y;		

		//アニメーション関係
		int m_ani_time; //アニメーションフレーム動作感覚
		int m_ani_frame;//描画フレーム
		int m_ani_max_time;   //アニメーション動作間隔最大値
		bool m_ani_start_flag;   //始まるフラグ

		bool m_trick_flag;	//弾と当たっているかどうかを調べる

};