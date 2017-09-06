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
	m_px = x * 64.0f;
	m_py = y * WATER_SIZE_HEIGHT;
}

//イニシャライズ
void CObjWater::Init()
{
	m_ani_time = 0;
	m_ani_frame = 1;  //静止フレームを初期にする
	m_ani_max_time = 17; //アニメーション間隔幅

	//当たり判定
	Hits::SetHitBox(this, m_px, m_py, WATER_SIZE_WIDTH, WATER_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_WATER, 1);
	m_water_gauge = 0.0f;
}

//アクション
void CObjWater::Action()
{
	m_ani_time += 1;

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);

	//アニメーションの感覚管理
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	//最後までアニメーションが進むと最初に戻る
	if (m_ani_frame == 2)
	{
		m_ani_frame = 0;
	}

	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);

	CHitBox* hitbox = Hits::GetHitBox(this);
	//マップオブジェクトを持ってくる
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

		// m_water_gaugeが64を越えたら処理ストップ
		if (m_water_gauge >= 64)
		{
			return;
		}

		m_water_gauge += 0.1; // 1ずつ増やしていく

		// hitboxが小さくなる
		hitbox->SetPos(m_px - obj_m->GetScrollX(), m_py - obj_m->GetScrollY() + m_water_gauge, WATER_SIZE_HEIGHT - m_water_gauge, WATER_SIZE_WIDTH);

}
//ドロー
void CObjWater::Draw()
{
	//画像の切り取り配列
	int AniData[2] =
	{
		0  , 1 ,
	};

	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * 128;
	src.m_right = 128.0f + AniData[m_ani_frame] * 128;
	src.m_bottom = 64.0f;

	//描画位置
	dst.m_top =  m_py + m_water_gauge - obj_m->GetScrollY();
	dst.m_left =  m_px - obj_m->GetScrollX();
	dst.m_right = dst.m_left + WATER_SIZE_WIDTH;
	dst.m_bottom = dst.m_top + WATER_SIZE_HEIGHT - m_water_gauge;

	//描画
	Draw::Draw(11, &src, &dst, color, 0);
	
	////描画位置
	//dst.m_top    = m_py + m_water_gauge;
	//dst.m_left   = m_px;
	//dst.m_right  = dst.m_left + BLOCK_SIZE; 
	//dst.m_bottom = 512.0f     + BLOCK_SIZE; // bottomは座標を固定する

	////描画
	//Draw::Draw(8, &src, &dst, color, 0.0f);
	/*
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//描画位置
	dst.m_top    = m_py + m_water_gauge;
	dst.m_left   = m_px;
	dst.m_right  = dst.m_left + BLOCK_SIZE; 
	dst.m_bottom = 512.0f     + BLOCK_SIZE; // bottomは座標を固定する
	*/
	////描画
	//Draw::Draw(8, &src, &dst, color, 0.0f);
}