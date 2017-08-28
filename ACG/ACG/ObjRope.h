#pragma once
//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：リフト
class CObjRope :public CObj
{
public:
	CObjRope(float x, float y); // コンストラクタ
	~CObjRope() {};	// デストラクタ
	void Init();	// イニシャライズ
	void Action();	// アクション
	void Draw();	// ドロー

private:
	float m_x;	// リフトX座標
	float m_y; // リフトY座標
};
