#pragma once
//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：トゲ
class CObjNeedle:public CObj
{
public:
	CObjNeedle(int x, int y);	// コンストラクタ
	~CObjNeedle() {};			// デストラクタ
	void Init();				// イニシャライズ
	void Action();				// アクション
	void Draw();				// ドロー

private:
	float m_px;		//位置X
	float m_py;		//位置Y
	//マップの要素数
	int m_map_x;
	int m_map_y;
	float m_needle_gauge; //針の沈む速度
	int   m_time;         //針の沈んだあとのタイム
};
