#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjReflectBlock.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjReflectBlock::CObjReflectBlock(int x, int y)
{
	m_x = x * BLOCK_SIZE;
	m_y = y * BLOCK_SIZE;
}

//イニシャライズ
void CObjReflectBlock::Init()
{
	//当たり判定
	Hits::SetHitBox(this, m_x, m_y, BLOCK_SIZE, BLOCK_SIZE, ELEMENT_BLOCK, OBJ_REFLECT_BLOCK, 1);
}

//アクション
void CObjReflectBlock::Action()
{
	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_x, m_y);
}

//ドロー
void CObjReflectBlock::Draw()
{


}