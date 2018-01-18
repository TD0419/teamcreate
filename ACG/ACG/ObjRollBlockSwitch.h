#pragma once

//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//クラス　回転ブロックスイッチ
class CObjRollBlockSwitch : public CObj
{
public:
	CObjRollBlockSwitch(float x, float y, CObjRollBlock* p);		//コンストラクタ
	~CObjRollBlockSwitch() {};	//デストラクタ

	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
private:
	//ロープと回転ブロックスイッチの位置を調整する関数
	void PositionAdjustment();
private:
	//位置
	float m_px;
	float m_py;
	float m_r;
	bool  m_rotation_flag; //回転をするかどうかのフラグ　true=回転する、回転している　false=回転しない、回転していない

	//ブロックのポジション
	float m_base_block_px;
	float m_base_block_py;

	//スイッチが作用させる回転ブロックのポインタ
	CObjRollBlock* mp_base_block;

	//ロープと衝突しているかどうかフラグ
	//true = 衝突している　false = 衝突していない
	bool m_rope_hit_flag;
};