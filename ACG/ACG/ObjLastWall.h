#pragma once

//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：Water(ギミック)
class CObjLastWall :public CObj
{
	public:
		CObjLastWall(int x, int y); 	//コンストラクタ
		~CObjLastWall() {};			//デストラクタ
		void Init();				//イニシャライズ
		void Action();				//アクション
		void Draw();				//ドロー

		bool GateOpenflag;
	private:
		float m_px;	//X座標
		float m_py;	//Y座標

					//マップ上の位置（要素数）
		int m_map_x;//X
		int m_map_y;//Y
		float m_wall_gauge;//壁の高さ管理
		bool m_look_unlock_flag;//ボタンがおされたかのフラグ
};