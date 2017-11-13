#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：第五ステージのボス
class CObjStage5Boss :public CObj
{
public:
	CObjStage5Boss(int x, int y);      //コンストラクタ
	~CObjStage5Boss() {};	//デストラクタ
	void Init();	        //イニシャライズ
	void Action();	        //アクション
	void Draw();	        //ドロー
private:
	float m_px;	 // 第五ボスX座標
	float m_py;	 // 第五ボスY座標
	float m_vx;  // 第五ボスX軸移動ベクトル
	float m_vy;  // 第五ボスY軸移動ベクトル

	int m_hp;    // 第五ボスのＨＰ
};