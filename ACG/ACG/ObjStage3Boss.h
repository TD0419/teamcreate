#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：第三ステージのボス
class CObjStage3Boss :public CObj
{
public:
	CObjStage3Boss(int x ,int y);       //コンストラクタ
	~CObjStage3Boss() {};	//デストラクタ
	void Init();	        //イニシャライズ
	void Action();	        //アクション
	void Draw();	        //ドロー
private:
	float m_x;	 // 第三ボスX座標
	float m_y;	 // 第三ボスY座標
	float m_vx;  // 第三ボスX軸方向のベクトル
	float m_vy;  // 第三ボスY軸方向のベクトル

	int m_hp;    // 第三ボスのＨＰ

};