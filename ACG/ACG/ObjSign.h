#pragma once
//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：リフト
class CObjSign :public CObj
{
public:
	CObjSign(float x, float y); // コンストラクタ
	~CObjSign() {};	// デストラクタ
	void Init();	// イニシャライズ
	void Action();	// アクション
	void Draw();	// ドロー

private:
	float m_x;	// リフトX座標
	float m_y; // リフトY座標
};
