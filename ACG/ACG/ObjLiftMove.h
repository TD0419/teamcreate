#pragma once
//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：動くリフト
class CObjLiftMove :public CObj
{
public:
	CObjLiftMove(int x, int y); // コンストラクタ
	~CObjLiftMove() {};			// デストラクタ
	void Init();			// イニシャライズ
	void Action();			// アクション
	void Draw();			// ドロー
	void HeroRide();		//　主人公が乗っているときの処理
							//アクセサ-----------------------------------------
	float GetVecX() { return m_vx; }	//移動ベクトルXを返す
	float GetVecY() { return m_vy; }	//移動ベクトルYを返す

private:
	float m_px;		// 動くリフトX座標
	float m_py;		// 動くリフトY座標
	float m_vx;		// 動くリフトの移動ベクトルX
	float m_vy;		// 動くリフトの移動ベクトルY

	//マップ上の位置（要素数）
	int m_map_x;//X
	int m_map_y;//Y
};
