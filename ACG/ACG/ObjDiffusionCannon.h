#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：拡散弾発射装置
class CObjDiffusionCannon :public CObj
{
public:
	CObjDiffusionCannon(int x, int y);	// コンストラクタ
	~CObjDiffusionCannon() {};			// デストラクタ
	void Init();				// イニシャライズ
	void Action();				// アクション
	void Draw();				// ドロー

	//アクセサ
	float GetPosX(){ return m_px; }
	float GetPosY() { return m_py; }

private:
	float m_px;		//位置X
	float m_py;		//位置Y
	int m_time;   //拡散弾の出るタイム
	int m_map_x;	//マップの要素番号
	int m_map_y;	//マップの要素番号
};
