//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjButton.h"
#include "Function.h"
//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjButton::CObjButton(int x, int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
}

//イニシャライズ
void CObjButton::Init()
{
	m_trick_flag = false;

	m_ani_time = 0;
	m_ani_frame = 0;  //静止フレームを初期にする
	m_ani_max_time = 8; //アニメーション間隔幅
	m_ani_start_flag = false;//アニメフラグOFF
	//当たり判定
	Hits::SetHitBox(this, m_px, m_py, 36, 32, ELEMENT_GIMMICK, OBJ_BUTTON, 1);
}

//アクション
void CObjButton::Action()
{
	// ボタンが押されたら
	if (m_trick_flag == true)
	{
		m_ani_start_flag = true; // フラグオン
	}
	HitBox* hit = Hits::GetHitBox(this);
	
	// 弾と接触しているかどうかを調べる
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{
		m_trick_flag = true; //弾とあたっているならtrueを入れる

	}

	//アニメフラグONだと
	if (m_ani_start_flag == true&&m_ani_frame!=1)
	{
		m_ani_time += 1;
		//アニメーションの感覚管理
		if (m_ani_time > m_ani_max_time)
		{
			m_ani_frame += 1;
			m_ani_time = 0;
		}

		//最後までアニメーションが進むと存在を消す
		if (m_ani_frame == 1)
		{
			m_ani_frame = 1;
			return;
		}
	}

	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px+13, m_py);

}

//ドロー
void CObjButton::Draw()
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
	src.m_left = AniData[m_ani_frame] * BUTTON_SIZE;
	src.m_right = src.m_left+BUTTON_SIZE;
	src.m_bottom = src.m_top + BUTTON_SIZE;

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY()-16;
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + BUTTON_SIZE;
	dst.m_bottom = dst.m_top + BUTTON_SIZE;

	
	//描画
	Draw::Draw(20, &src, &dst, color, 0.0f);
}