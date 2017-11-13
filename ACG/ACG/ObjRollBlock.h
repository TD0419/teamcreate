#pragma once

//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//クラス　回転ブロック
class CObjRollBlock : public CObj
{
public:
	CObjRollBlock(int x,int y, int pattan) ;		//コンストラクタ
	~CObjRollBlock() {};	//デストラクタ

	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
private:
	//オブジェクトの位置
	float m_px;		
	float m_py;		
	
	//回転の中心位置
	float m_center_x;
	float m_center_y;

	//回転後のポジションと中心位置の差分
	float m_difference_x;
	float m_difference_y;

	float m_r;		//回転角
	int m_count;	//回転の制御用カウンター
	int m_pattan;	//タイプ(1:一定時間で回転,2：ロープで引っ張って)
	bool m_roll_flag;//回転するかどうかのフラグ
};