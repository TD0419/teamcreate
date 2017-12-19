#pragma once

//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：ロープでぶら下がることができるギミック
class CObjTarzanPoint :public CObj
{
public:
	CObjTarzanPoint(int x,int y,bool look_flag); 	//コンストラクタ
	~CObjTarzanPoint() {};				//デストラクタ
	void Init();						//イニシャライズ
	void Action();						//アクション
	void Draw();						//ドロー

private:
	float m_px;							//X座標
	float m_py;							//Y座標
	//マップの要素数
	int m_map_x;
	int m_map_y;
	bool m_look_flag;	//表示や判定をするかのフラグ
	
};