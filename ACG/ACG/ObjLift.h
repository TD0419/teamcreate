#pragma once
//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：リフト
class CObjLift :public CObj
{
public:
	CObjLift(int x, int y); // コンストラクタ
	CObjLift(int px, int py, float vx, float vy, float width_max, float length_max);//コンストラクタ
	~CObjLift() {};			// デストラクタ
	void Init();			// イニシャライズ
	void Action();			// アクション
	void Draw();			// ドロー
	void HeroRide();		//　主人公が乗っているときの処理
	//アクセサ-----------------------------------------
	float GetVecX() { return m_vx; }	//移動ベクトルXを返す
	float GetVecY() { return m_vy; }	//移動ベクトルYを返す

private:
	float m_px;		// リフトX座標
	float m_py;		// リフトY座標
	float m_vx;		// リフトの移動ベクトルX
	float m_vy;		// リフトの移動ベクトルY
	float m_width_max;	//左右の最大移動量
	float m_length_max;	//上下の最大移動量

	float m_move_x;//動いた距離X
	float m_move_y;//動いた距離Y

};
