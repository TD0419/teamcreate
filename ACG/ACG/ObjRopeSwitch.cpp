#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjRopeSwitch.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjRopeSwitch::CObjRopeSwitch(int x, int y)
{
	m_px = x * ROPE_SWITCH_SIZE;
	m_py = y * ROPE_SWITCH_SIZE;

	m_rope_flag = false;
}

//イニシャライズ
void CObjRopeSwitch::Init()
{
	//当たり判定
	Hits::SetHitBox(this, m_px, m_py, 20, 20, ELEMENT_GIMMICK, OBJ_ROPE_SWITCH, 1);
}

//アクション
void CObjRopeSwitch::Action()
{
	//自身のHitBoxをもってくる
	CHitBox*hit = Hits::GetHitBox(this);

	//ロープが当たっていれば
	if (hit->CheckObjNameHit(OBJ_ROPE) != nullptr)
	{
		m_rope_flag = true;//フラグをONにする
	}
	else if(hit->CheckObjNameHit(OBJ_ROPE) == nullptr)
	{
		m_rope_flag = false;//フラグをOFFにする
	}

	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px+23.0f, m_py+32.0f);
}

//ドロー
void CObjRopeSwitch::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//描画位置
	dst.m_top = 0.0f + m_py - objmap->GetScrollY();
	dst.m_left = 0.0f + m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + ROPE_SWITCH_SIZE;
	dst.m_bottom = dst.m_top + ROPE_SWITCH_SIZE;

	//描画
	Draw::Draw(13, &src, &dst, color, 0);
}