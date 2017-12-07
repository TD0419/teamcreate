#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjNeedleStand.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjNeedleStand::CObjNeedleStand(int x, int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
}

//イニシャライズ
void CObjNeedleStand::Init()
{
	//当たり判定用HitBoxを作成                          
	Hits::SetHitBox(this, m_px, m_py, NEEDLE_STAND_SIZE, NEEDLE_STAND_SIZE, ELEMENT_GIMMICK, OBJ_NEEDLE_STAND, 1);

}

//アクション
void CObjNeedleStand::Action()
{
	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);

	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py - 32.0f);
}

//ドロー
void CObjNeedleStand::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//針の土台---------------------------------------------------

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + 640.0f;
	src.m_bottom = src.m_top + 64.0f;

	//描画位置
	dst.m_top = m_py + 32.0f - objmap->GetScrollY() - NEEDLE_STAND_SIZE;
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + NEEDLE_STAND_SIZE;
	dst.m_bottom = dst.m_top + NEEDLE_STAND_SIZE;

	//描画
	Draw::Draw(GRA_WIRE_MASH, &src, &dst, color, 0.0f);
	//-------------------------------------------------------
}