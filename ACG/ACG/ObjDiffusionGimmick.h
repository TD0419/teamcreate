#pragma once
//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：拡散弾発射装置
class CObjDiffusionGimmick :public CObj
{
public:
	CObjDiffusionGimmick(float x, float y);	// コンストラクタ
	~CObjDiffusionGimmick() {};			// デストラクタ
	void Init();				// イニシャライズ
	void Action();				// アクション
	void Draw();				// ドロー

private:
	float m_px;		//位置X
	float m_py;		//位置Y

};
