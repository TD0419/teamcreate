#pragma once
//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：トゲ
class CObjNeedleStand :public CObj
{
public:
	CObjNeedleStand(int x, int y);	// コンストラクタ
	~CObjNeedleStand() {};			// デストラクタ
	void Init();				// イニシャライズ
	void Action();				// アクション
	void Draw();				// ドロー

private:
	float m_px;		//位置X
	float m_py;		//位置Y
};
