#pragma once

//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：スルーブロック
class CObjThroughBlock :public CObj
{
public:
	CObjThroughBlock(int x, int y); 	//コンストラクタ
	~CObjThroughBlock() {};				//デストラクタ
	void Init() {};						//イニシャライズ
	void Action();						//アクション
	void Draw();						//ドロー
	
private:
	float m_px;	//X座標
	float m_py;	//Y座標
	int m_map_x;//マップの要素数
	int m_map_y;
};
