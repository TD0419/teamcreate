//使用するヘッダーファイル　
#include "GameL\HitBoxManager.h"
#include "GameHead.h"
#include "ObjWater.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjWater::CObjWater(float x, float y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//イニシャライズ
void CObjWater::Init()
{
	//当たり判定
	Hits::SetHitBox(this, m_px, m_py, WATER_SIZE, WATER_SIZE, ELEMENT_WATER, OBJ_WATER, 1);
}

//アクション
void CObjWater::Action()
{
}

//ドロー
void CObjWater::Draw()
{
}