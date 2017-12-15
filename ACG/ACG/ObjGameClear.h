#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

#define FONT_SIZE_GC (86.0f)	//文字のサイズ(ゲームクリア用)

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