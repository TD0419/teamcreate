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

		float m_sink;		// ボタンが沈む高さ

		bool m_trick_flag;	//弾と当たっているかどうかを調べる
};