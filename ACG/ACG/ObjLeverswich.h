#pragma once
//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：リフト
class CObjLeverSwich :public CObj
{
public:
	CObjLeverSwich(float x, float y); // コンストラクタ
	~CObjLeverSwich() {};	// デストラクタ
	void Init();	// イニシャライズ
	void Action();	// アクション
	void Draw();	// ドロー

private:
	float m_x;	// リフトX座標
	float m_y; // リフトY座標
};
