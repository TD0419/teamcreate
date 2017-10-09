#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjTitle :public CObj
{
public:
	CObjTitle() {}; 	//コンストラクタ
	~CObjTitle() {};	//デストラクタ
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー
private:
};
