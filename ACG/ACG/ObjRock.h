#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：岩
class CObjRock :public CObj
{
public:
	CObjRock(int x, int y); 	//コンストラクタ
	~CObjRock() {};	//デストラクタ
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
private:
	float m_px;	//岩X座標
	float m_py;	//岩Y座標
};