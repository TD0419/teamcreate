#pragma once

//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：Water
class CObjWater :public CObj
{
public:
	CObjWater(float x, float y); 	//コンストラクタ
	~CObjWater() {};	//デストラクタ
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	
private:
	float m_px;	//X座標
	float m_py;	//Y座標
};