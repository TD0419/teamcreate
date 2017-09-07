//使用するヘッダーファイル　
#include "GameL\HitBoxManager.h"
#include "GameL\WinInputs.h"
#include "GameHead.h"
#include "ObjWater.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjWater::CObjWater(int x, int y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * WATER_SIZE_HEIGHT;
}

//イニシャライズ
void CObjWater::Init()
{

	//当たり判定
	Hits::SetHitBox(this, m_px, m_py, BLOCK_SIZE, WATER_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_WATER, 1);
	m_water_gauge = 0.0f;
}

//アクション
void CObjWater::Action()
{	
	CHitBox* hitbox = Hits::GetHitBox(this);
	//マップオブジェクトを持ってくる
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

		// m_water_gaugeが64を越えたら処理ストップ
		if (m_water_gauge >= 64)
		{
			this->SetStatus(false);		//自身に削除命令を出す
			Hits::DeleteHitBox(this);	//岩が所有するHitBoxに削除する
			return;
		}

		m_water_gauge += 0.5f; // 1ずつ増やしていく

	// hitboxが小さくなる
	hitbox->SetPos(m_px - obj_m->GetScrollX(), m_py - obj_m->GetScrollY() + m_water_gauge, BLOCK_SIZE - m_water_gauge, BLOCK_SIZE);

}
//ドロー
void CObjWater::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 128.0f ;
	src.m_bottom = 64.0f;

	//描画位置
	dst.m_top = m_py + m_water_gauge - obj_m->GetScrollY();
	dst.m_left = m_px - obj_m->GetScrollX();
	dst.m_right = dst.m_left + BLOCK_SIZE;
	dst.m_bottom = dst.m_top + WATER_SIZE_HEIGHT - m_water_gauge;
	//描画
	Draw::Draw(11, &src, &dst, color, 0.0f);
}