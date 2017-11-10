#pragma once

//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//クラス　回転ブロック
class CObjRollBlock : CObj
{
	CObjRollBlock(int x,int y) ;		//コンストラクタ
	~CObjRollBlock() {};	//デストラクタ

	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
private:
	float m_px;		//オブジェクトの位置X
	float m_py;		//オブジェクトの位置Y
	float m_r;		//回転角
	int m_count;	//回転の制御用カウンター
	bool m_roll_flag;//回転するかどうかのフラグ
};