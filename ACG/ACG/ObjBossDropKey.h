#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：ボス鍵(ドロップアイテム)
class CObjBossDropKey :public CObj
{
public:
	CObjBossDropKey(int x, int y);  //コンストラクタ
	~CObjBossDropKey() {};			//デストラクタ
	void Init();					//イニシャライズ
	void Action();					//アクション
	void Draw();					//ドロー
private:
	float m_px;	   // ボス鍵X座標
	float m_py;	   // ボス鍵Y座標


};
