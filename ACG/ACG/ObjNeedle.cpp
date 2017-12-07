#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjNeedle.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjNeedle::CObjNeedle(int x, int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
}

//イニシャライズ
void CObjNeedle::Init()
{
	m_needle_gauge = 0.0f;
	m_time = 0;

    //当たり判定用HitBoxを作成                          
	Hits::SetHitBox(this, m_px, m_py, NEEDLE_SIZE_WIDTH, NEEDLE_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_NEEDLE, 1);

}

//アクション
void CObjNeedle::Action()
{
	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//針が最後まで出ていない時
	if (m_needle_gauge != 64)
		m_needle_gauge++;
	else //針が最後まで出た場合
	{
		m_time++;
		hit->SetInvincibility(true);//針の判定をなくす
		if (m_time == 120) //120フレーム経ったら針を出す
		{
			m_needle_gauge = 0;
 			m_time = 0;
			hit->SetInvincibility(false);//針の判定をつける
		}
		
	}
	// hitboxが小さくなる
	hit->SetPos(m_px - objmap->GetScrollX(), m_py - 64.0f - objmap->GetScrollY() + m_needle_gauge / 2  , NEEDLE_SIZE_WIDTH, NEEDLE_SIZE_HEIGHT - m_needle_gauge / 2 );

}

//ドロー
void CObjNeedle::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//針-------------------------------------------------------
	//切り取り位置
	src.m_top = 32.0f;
	src.m_left = 0.0f; 
	src.m_right = src.m_left + 32.0f;
	src.m_bottom = src.m_top - 32.0f  + m_needle_gauge / 2;

	//描画位置
	dst.m_top = m_py + m_needle_gauge / 2 - objmap->GetScrollY() - NEEDLE_SIZE_WIDTH;
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + NEEDLE_SIZE_WIDTH;
	dst.m_bottom = dst.m_top + NEEDLE_SIZE_HEIGHT - m_needle_gauge / 2;

	//描画
	Draw::Draw(GRA_NEEDLE, &src, &dst, color, 0.0f);

	//------------------------------------------------------------
}