#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//------------------------------------------

//オブジェクト：第五ステージのボスの腕
class CObjStage5BossArms :public CObj
{
public:
	CObjStage5BossArms(int x, int y);      //コンストラクタ
	~CObjStage5BossArms() {};	//デストラクタ
	void Init();	        //イニシャライズ
	void Action();	        //アクション
	void Draw();	        //ドロー
private:
	float m_px;	 // 第五ボスの腕X座標
	float m_py;	 // 第五ボスの腕Y座標
	float m_vx;  // 第五ボスの腕X軸移動ベクトル
	float m_vy;  // 第五ボスの腕Y軸移動ベクトル

	int m_hp;    // 第五ボスの腕のＨＰ
};