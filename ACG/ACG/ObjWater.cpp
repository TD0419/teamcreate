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
	m_map_x = x;
	m_map_y = y;
	m_px = x *  WATER_SIZE_WIDTH;
	m_py = y * WATER_SIZE_HEIGHT;
}

//イニシャライズ
void CObjWater::Init()
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
void CObjWater::Action()
{
	m_ani_time += 1;

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);

	//マップオブジェクトを持ってくる
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);
	
	int map_num= obj_m->GetMap(m_map_x , m_map_y - 1);
	
	//1つ上のマスが水なら
 	if( map_num == MAP_WATER)
	{
		return;
	}

	//アニメーションを開始するのでフラグをオンにする
	m_ani_start = true;

	// m_water_gaugeが64を越えたら処理ストップ
	if (m_water_gauge >= WATER_SIZE_HEIGHT)
	{
		Hits::DeleteHitBox(this);//hitbox削除
		obj_m->SetMap(m_map_x, m_map_y, MAP_SPACE);//マップの数値を空にする
		this->SetStatus(false);//自身
		return;
	}
	else
	{
		m_water_gauge += 0.2f; // 1ずつ増やしていく
		// hitboxが小さくなる
        hit->SetPos(m_px - obj_m->GetScrollX(), m_py - obj_m->GetScrollY() + m_water_gauge, WATER_SIZE_HEIGHT - m_water_gauge, WATER_SIZE_WIDTH);


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
	}
	
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
	src.m_left = AniData[m_ani_frame] * WATER_SIZE_WIDTH;
	src.m_right = src.m_left+WATER_SIZE_WIDTH;
	src.m_bottom = src.m_top+WATER_SIZE_HEIGHT;

	//描画位置
	dst.m_top = m_py + m_water_gauge - obj_m->GetScrollY();
	dst.m_left = m_px - obj_m->GetScrollX();
	dst.m_right = dst.m_left + BLOCK_SIZE;
	dst.m_bottom = dst.m_top + WATER_SIZE_HEIGHT - m_water_gauge;

	
	if(m_ani_start==false)
		Draw::Draw(12, &src, &dst, color, 0);//水（波なしの画像）
	else
		Draw::Draw(11, &src, &dst, color, 0);//水（波有の画像　アニメーション付き）
}