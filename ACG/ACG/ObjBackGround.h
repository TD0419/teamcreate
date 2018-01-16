#pragma once
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：バッググラウンド(背景)
class CObjBackGround :public CObj
{
public:
	CObjBackGround() {};	// コンストラクタ
	~CObjBackGround() {};			// デストラクタ
	void Init() {};					// イニシャライズ
	void Action() {};				// アクション
	void Draw();					// ドロー
};