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
	m_py = y * BLOCK_SIZE;
}

//イニシャライズ
void CObjWater::Init()
{

	//当たり判定
	Hits::SetHitBox(this, m_px, m_py, BLOCK_SIZE, BLOCK_SIZE, ELEMENT_PLAYER, OBJ_WATER, 1);
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
		return;
	}

	m_water_gauge+=1; // 1ずつ増やしていく

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

	//描画位置
	dst.m_top    = m_py - obj_m->GetScrollY() + m_water_gauge;
	dst.m_left   = m_px - obj_m->GetScrollX();
	dst.m_right  = dst.m_left + BLOCK_SIZE; 
	dst.m_bottom = 512.0f - obj_m->GetScrollY() + BLOCK_SIZE; // bottomは座標を固定する

	//描画
	Draw::Draw(8, &src, &dst, color, 0.0f);
}