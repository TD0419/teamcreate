#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjWood.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjWood::CObjWood(int x, int y)
{
	m_px = x * WOOD_SIZE;
	m_py = y * WOOD_SIZE;
}

//イニシャライズ
void CObjWood::Init()
{
	//当たり判定
	Hits::SetHitBox(this, m_px, m_py, WOOD_SIZE, WOOD_SIZE, ELEMENT_GIMMICK, OBJ_WOOD, 1);

}

//アクション
void CObjWood::Action()
{
	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);

}

//ドロー
void CObjWood::Draw()
{

}