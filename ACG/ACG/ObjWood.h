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

	private:
		float m_px;			//X座標(空気画像を含む)
		float m_py;			//Y座標(空気画像を含む)
		float m_wood_image_x;//木の画像(左上)のX位置
		float m_wood_image_y;//木の画像(左上)のY位置
		float m_r;			//回転角度
		bool m_audio_start_flag;//木の音を鳴らすためのフラグ変数
};
