#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：ボタン
class CObjButton : public CObj
{
	public:
		CObjButton(float x, float y);
		~CObjButton() {};
		void Init();	//イニシャライズ
		void Action();  //アクション
		void Draw();	//ドロー

		/*-----------------------アクセサ-------------------------*/
		bool GetTrickFlag() { return m_trick_flag; } //弾とあたっているかどうかを返す

	private:
		float m_button_x; //ボタンX位置
		float m_button_y; //ボタンY位置

		bool m_trick_flag; //縄とあっているかどうかを入れる変数

};