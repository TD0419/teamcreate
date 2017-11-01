#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjLeverSwich.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjLeverSwich::CObjLeverSwich(float x, float y)
{
	m_px = x * LEVER_SWITCH_SIZE;
	m_py = y * LEVER_SWITCH_SIZE;
}

//イニシャライズ
void CObjLeverSwich::Init()
{
	m_ani_time = 0;
	m_ani_frame = 0;	//静止フレームを初期にする
	m_ani_max_time = 4; //アニメーション間隔幅
	m_water_con = false;
	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, LEVER_SWITCH_SIZE, LEVER_SWITCH_SIZE, ELEMENT_GIMMICK, OBJ_LEVER_SWICH, 1);
}

//アクション
void CObjLeverSwich::Action()
{
	//レバースイッチのHitBox更新用ポインター取得
	CHitBox* hit = Hits::GetHitBox(this);

	//ロープとあたったら描画を進める
	if (hit->CheckObjNameHit(OBJ_ROPE) != nullptr)
	{
		//水の判定をONにする
		m_water_con = true;

		m_ani_time += 1;

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

		// 木を回転させる----------------------------------
		
		// 木オブジェクトを持ってくる
		CObjWood* obj_wood = (CObjWood*)Objs::GetObj(OBJ_WOOD);

		// 木に回転フラグを立てる
		if (obj_wood != nullptr)
			obj_wood->Rotation(true);

		// ------------------------------------------------
		
	}

	

	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//ドロー
void CObjLeverSwich::Draw()
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
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = AniData[m_ani_frame] * 64;
	src.m_right = 64.0f + AniData[m_ani_frame] * 64;
	src.m_bottom = 64.0f;

	//描画位置
	dst.m_top = 0.0f + m_py - objmap->GetScrollY();
	dst.m_left = 0.0f + m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + LEVER_SWITCH_SIZE;
	dst.m_bottom = dst.m_top + LEVER_SWITCH_SIZE;

	//描画
	Draw::Draw(9, &src, &dst, color, 0);
}