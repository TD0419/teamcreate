#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：落ちる壁(ギミック)
class CObjFallingWalls :public CObj
{
public:
	CObjFallingWalls(int x, int y); 	//コンストラクタ
	~CObjFallingWalls() {};				//デストラクタ
	void Init();						//イニシャライズ
	void Action();						//アクション
	void Draw();						//ドロー
private:
	float m_px;							//落ちる壁(ギミック)X座標
	float m_py;							//落ちる壁(ギミック)Y座標
};