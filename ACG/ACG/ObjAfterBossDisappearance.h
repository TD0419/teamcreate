#pragma once

//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：ステージ５ボス消滅アニメージョン後のオブジェクト
class CObjAfterBossDisappearance :public CObj
{
public:
	CObjAfterBossDisappearance() {}; 	//コンストラクタ
	~CObjAfterBossDisappearance() {};							//デストラクタ
	void Init();												//イニシャライズ
	void Action();												//アクション
	void Draw();												//ドロー

private:
};