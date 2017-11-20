//使用するヘッダーファイル　
#include "GameL\HitBoxManager.h"
#include "GameL\WinInputs.h"
#include "GameL\Audio.h"
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
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//イニシャライズ
void CObjWater::Init()
{
	m_ani_time = 0;
	m_ani_frame = 0;  //静止フレームを初期にする
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

	//レバースイッチオブジェクトを持ってくる
	CObjLeverSwich* obj_lever = (CObjLeverSwich*)Objs::GetObj(OBJ_LEVER_SWICH);

	bool lever_swich = false;
	//レバースイッチオブジェクトが当たっているかどうかを調べる
	if (obj_lever != nullptr)
		lever_swich = obj_lever->GetWater();
	else
		lever_swich = false;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//アニメーションを開始するのでフラグをオンにする
	m_ani_start = true;
	
	// m_water_gaugeが192を越えたら処理ストップ
	if (m_water_gauge >= WATER_SIZE_HEIGHT)
	{
		Hits::DeleteHitBox(this);//hitbox削除
		objmap->SetMap(m_map_x, m_map_y, MAP_SPACE);//マップの数値を空にする
		this->SetStatus(false);//自身
		return;
	}
	else
	{
		//レバースイッチが押されていたら
		if (lever_swich == true)
		{
			m_water_gauge += 0.2f; // 1ずつ増やしていく
		}
	}

	// hitboxが小さくなる
	hit->SetPos(m_px - objmap->GetScrollX(), m_py - objmap->GetScrollY() + m_water_gauge, WATER_SIZE_WIDTH, WATER_SIZE_HEIGHT - m_water_gauge);

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
//ドロー
void CObjWater::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top = 0.0f + WATER_SIZE_HEIGHT * m_ani_frame;
	src.m_left =0.0f;
	src.m_right = src.m_left+WATER_SIZE_WIDTH;
	src.m_bottom =src.m_top+WATER_SIZE_HEIGHT;

	//描画位置
	dst.m_top = m_py + m_water_gauge - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + WATER_SIZE_WIDTH;
	dst.m_bottom = dst.m_top + WATER_SIZE_HEIGHT - m_water_gauge;

	Draw::Draw(GRA_AQUATIC, &src, &dst, color, 0);//水
}