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
	m_map_x = x;
	m_map_y = y;
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

	//画面外なら
	if (WindowCheck(m_px, m_py, NEEDLE_STAND_SIZE, NEEDLE_STAND_SIZE) == false)
	{
		WindowOutDelete(this, m_map_x, m_map_y);//削除処理(復活あり)
		return;
	}

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);

	//hit->CheckObjNameHit(OBJ_HERO)

	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//ドロー
void CObjNeedleStand::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + 64.0f;
	src.m_bottom = src.m_top + 64.0f;

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + NEEDLE_STAND_SIZE;
	dst.m_bottom = dst.m_top + NEEDLE_STAND_SIZE;

	//描画
	Draw::Draw(GRA_NEEDLE_STAND, &src, &dst, color, 0.0f);
}