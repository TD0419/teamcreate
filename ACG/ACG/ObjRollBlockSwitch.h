#pragma once

//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//クラス　回転ブロック
class CObjRollBlockSwitch : public CObj
{
public:
	CObjRollBlockSwitch(float x, float y, CObjRollBlock* p);		//コンストラクタ
	~CObjRollBlockSwitch() {};	//デストラクタ

	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー

	float GetRad() { return m_r; }//角度を返す

	//ブロックの位置を返す
	float GetX() { return m_px; }
	float GetY() { return m_py; }
private:
	//位置
	float m_px;
	float m_py;
	float m_r;

	//ブロックのポジション
	float m_base_block_px;
	float m_base_block_py;


	//スイッチが作用させる回転ブロックのポインタ
	CObjRollBlock* mp_base_block;

	bool m_pull_flag;//ロープで引かれているかどうかのフラグ
	
};