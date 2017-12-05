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
	//ステージ5ボスcppからの描画の都合で、xとyの型をintからfloatに変更しています。(描画で細かい値を使いたいため)
	CObjStage5BossArms(float x, float y ,int type);      //コンストラクタ
	~CObjStage5BossArms() {};	//デストラクタ
	void Init();	        //イニシャライズ
	void Action();	        //アクション
	void Draw();	        //ドロー


private:
	float m_px;	 // 第五ボスのアームX座標
	float m_py;	 // 第五ボスのアームY座標
	
	float m_vx;  // 第五ボスのアームX軸移動ベクトル
	float m_vy;  // 第五ボスのアームY軸移動ベクトル

	int m_arms_type;	 //第五ボスアームのタイプ(1…ライトアーム  2…レフトアーム)

	int m_arm_hp;    // 第五ボスのアームのＨＰ
	
	

};