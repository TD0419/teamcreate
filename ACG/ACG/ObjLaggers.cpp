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
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//描画位置
	dst.m_top = 0.0f + m_py - obj_m->GetScrollY();
	dst.m_left = 0.0f + m_px - obj_m->GetScrollX();
	dst.m_right = dst.m_left + LADDERS_SIZE;
	dst.m_bottom = dst.m_top + LADDERS_SIZE;

	//描画
	Draw::Draw(4, &src, &dst, color, 0);
}