#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：乗ると落ちるリフト(ギミック)
class CObjFallingLift :public CObj
{
public:
	CObjFallingLift(int x, int y); 		//コンストラクタ
	~CObjFallingLift() {};				//デストラクタ
	void Init();						//イニシャライズ
	void Action();						//アクション
	void Draw();						//ドロー
private:
	float m_px;							//落ちるリフト(ギミック)X座標
	float m_py;							//落ちるリフト(ギミック)Y座標
};
