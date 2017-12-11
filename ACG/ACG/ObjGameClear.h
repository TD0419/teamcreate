#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：クリア
class CObjGameClear : public CObj
{
public:
	CObjGameClear() {};		//コンストラクタ
	~CObjGameClear() {};	//デクスラクタ
	void Init();			//イニシャライズ
	void Action();			//アクション
	void Draw();			//ドロー

private:
	
};