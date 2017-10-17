#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：木(ギミック)
class CObjWood :public CObj
{
	public:
		CObjWood(int x, int y);				//コンストラクタ
		~CObjWood() {};						//デストラクタ
		void Init();						//イニシャライズ
		void Action();						//アクション
		void Draw();						//ドロー
		void HeroHit(float px, float py);	//主人公が触れたときの処理
		void Rotation(bool flag) { m_rota_flag = flag; } // 木を回転させるかどうかの管理をする関数
	private:
		float m_px;			//木X座標
		float m_py;			//木Y座標
		float m_r;			//回転角度
		bool  m_rota_flag;  //回転フラグ false:回転しない true:回転する
};
