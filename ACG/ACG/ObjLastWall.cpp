#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjLastWall.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjLastWall::CObjLastWall(int x, int y)
{
	m_px = x * 64;
	m_py = y * 64;
}

//イニシャライズ
void CObjLastWall::Init()
{
	m_ani_time = 0;
	m_ani_frame = 1;  //静止フレームを初期にする
	m_ani_max_time = 17; //アニメーション間隔幅
	m_ani_start = false;

	//当たり判定																
	Hits::SetHitBox(this, m_px, m_py, WATER_SIZE_WIDTH, WATER_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_WATER, 1);
	m_water_gauge = 0.0f;
}

//アクション
void CObjLastWall::Action()
{
	m_ani_time += 1;

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);

	//	//アニメーションの感覚管理
	//	if (m_ani_time > m_ani_max_time)
	//	{
	//		m_ani_frame += 1;
	//		m_ani_time = 0;
	//	}

	//	//最後までアニメーションが進むと最初に戻る
	//	if (m_ani_frame == 2)
	//	{
	//		m_ani_frame = 0;
	//	}
	//}
}

//ドロー
void CObjLastWall::Draw()
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
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + 96;
	dst.m_bottom = dst.m_top + 512;

	//描画(上の部分)
	Draw::Draw(22, &src, &dst, color, 0.0f);

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY()+467;
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + 96;
	dst.m_bottom = dst.m_top + 185;
	//描画(下の部分)
	Draw::Draw(21, &src, &dst, color, 0.0f);
}