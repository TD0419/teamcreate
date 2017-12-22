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
	m_map_x = x;
	m_map_y = y;
}

//イニシャライズ
void CObjNeedle::Init()
{
	m_needle_gauge = 0.0f;
	m_time = 0;
	m_over_or_under = false;//true…トゲの台の上にある　false…台の下にある

	//マップのオブジェクト情報を取得
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//トゲの台のオブジェクト情報を取得
	CObjNeedleStand* obj_needle_stand = (CObjNeedleStand*)Objs::GetObj(OBJ_NEEDLE_STAND);

	//マップ上(csvデータ)でトゲの番号の下に台の番号があるかを調べる
	int stand_block_num = objmap->GetMap((int)m_px / ((int)BLOCK_SIZE), ((int)m_py / ((int)BLOCK_SIZE)) + 1);

	//下にトゲの台(番号)があれば、上向きのトゲを表示させる
	if ( stand_block_num == MAP_NEEDLE_STAND)
	{
		//トゲの台の上にあると判別する
		m_over_or_under = true;//上向きのトゲを表示するための処理

	}
	
	//当たり判定用HitBoxを作成                          
	Hits::SetHitBox(this, m_px, m_py, NEEDLE_SIZE_WIDTH, NEEDLE_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_NEEDLE, 1);

}

//アクション
void CObjNeedle::Action()
{
	////画面外なら
	//if (WindowCheck(m_px, m_py, NEEDLE_SIZE_WIDTH, NEEDLE_SIZE_HEIGHT) == false)
	//{
	//	WindowOutDelete(this, m_map_x, m_map_y);//削除処理(復活あり)
	//	return;
	//}

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
		if (m_time == 240) //120フレーム経ったら針を出す
		{
			m_needle_gauge = 0;
 			m_time = 0;
			hit->SetInvincibility(false);//針の判定をつける
		}
		
	}
	//下向きのトゲ時の当たり判定減少処理
	if (m_over_or_under == false)
	{
		// hitboxが小さくなる
		hit->SetPos(m_px - objmap->GetScrollX(), m_py - objmap->GetScrollY(), NEEDLE_SIZE_WIDTH, NEEDLE_SIZE_HEIGHT - m_needle_gauge / 2);

	}
	//上向きのトゲ時の当たり判定減少処理
	else if (m_over_or_under == true)
	{
		hit->SetPos(m_px - objmap->GetScrollX(), m_py + NEEDLE_SIZE_HEIGHT - objmap->GetScrollY() + m_needle_gauge / 2, NEEDLE_SIZE_WIDTH, NEEDLE_SIZE_HEIGHT - m_needle_gauge / 2);

	}
}

//ドロー
void CObjNeedle::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);
	
	//下向きのトゲを描画する
	if (m_over_or_under == false)
	{
		//切り取り位置
		src.m_top = 0.0f + m_needle_gauge / 2;
		src.m_left = 0.0f;
		src.m_right = src.m_left + NEEDLE_SIZE_WIDTH;
		src.m_bottom = src.m_top + NEEDLE_SIZE_HEIGHT;

		//描画位置
		dst.m_top = m_py - objmap->GetScrollY();
		dst.m_left = m_px - objmap->GetScrollX();
		dst.m_right = dst.m_left + NEEDLE_SIZE_WIDTH;
		dst.m_bottom = dst.m_top + NEEDLE_SIZE_HEIGHT - m_needle_gauge / 2;
	}
	//上向きのトゲを描画する
	else if (m_over_or_under == true)
	{
		//切り取り位置
		src.m_top = NEEDLE_SIZE_HEIGHT;
		src.m_left = 0.0f;
		src.m_right = src.m_left + NEEDLE_SIZE_WIDTH;
		src.m_bottom = 0.0f + m_needle_gauge / 2;

		//描画位置
		dst.m_top = NEEDLE_SIZE_HEIGHT + m_py - objmap->GetScrollY() + m_needle_gauge / 2;
		dst.m_left = m_px - objmap->GetScrollX();
		dst.m_right = dst.m_left + NEEDLE_SIZE_WIDTH;
		dst.m_bottom = (NEEDLE_SIZE_HEIGHT + NEEDLE_SIZE_HEIGHT) + m_py - objmap->GetScrollY();
	}

	//描画
	Draw::Draw(GRA_NEEDLE, &src, &dst, color, 0.0f);
}