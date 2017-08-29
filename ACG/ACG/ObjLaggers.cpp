#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjLadders.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjLadders::CObjLadders(int x, int y)
{
	m_px = x * LADDERS_SIZE;
	m_py = y * LADDERS_SIZE;
}

//イニシャライズ
void CObjLadders::Init()
{
	//当たり判定
	Hits::SetHitBox(this, m_px, m_py, LADDERS_SIZE, LADDERS_SIZE, ELEMENT_GIMMICK, OBJ_LADDERS, 1);
}

//アクション
void CObjLadders::Action()
{

	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);

}

//ドロー
void CObjLadders::Draw()
{

}