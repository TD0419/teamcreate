#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//描画位置の補正用マクロ--------------------

//胴腕接続電気(左腕部分)の描画位置の補正値
#define ELECTRIC_L_CORRECTION_HEIGHT   (2.0f)		//縦
#define ELECTRIC_L_CORRECTION_WIDTH	 (248.0f)		//横

//胴腕接続電気(右腕部分)の描画位置の補正値
#define ELECTRIC_R_CORRECTION_HEIGHT  (15.0f)		//縦
#define ELECTRIC_R_CORRECTION_WIDTH	 (208.0f)		//横

//眼球の描画位置の補正値
#define EYE_CORRECTION_HEIGHT		 (102.0f)		//縦
#define EYE_CORRECTION_WIDTH	      (64.0f)		//横

//------------------------------------------

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