//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

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
	m_map_x = x;
	m_map_y = y;
}

//イニシャライズ
void CObjButton::Init()
{
	m_trick_flag = false;

	m_ani_time = 0;
	m_ani_frame = 0;  //静止フレームを初期にする
	m_ani_max_time = 8; //アニメーション間隔幅
	m_ani_start_flag = false;//アニメフラグOFF
	m_callout_time = 0;
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
		m_callout_time++;
	}
	HitBox* hit = Hits::GetHitBox(this);
	
	// 弾と接触しているかどうかを調べる
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{
		m_trick_flag = true; //弾とあたっているならtrueを入れる
	}

	//アニメフラグONだと
	if (m_ani_start_flag == true && m_ani_frame != 1)
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
		Audio::Start(BUTTON);

	}

	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px+13.0f, m_py);
}

//ドロー
void CObjButton::Draw()
{
	//主人公オブジェクトを持ってくる
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

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
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + BUTTON_SIZE;
	dst.m_bottom = dst.m_top + BUTTON_SIZE;

	//描画
	Draw::Draw(GRA_BUTTON, &src, &dst, color, 0.0f);

	if (m_callout_time>0&&m_callout_time < 300)
	{
		//切り取り位置
		src.m_top = 0.0f;
		src.m_left = 296.0f;
		src.m_right = 593.0f;
		src.m_bottom = 128.0f;

		//描画位置
		dst.m_top =   objhero->GetPosY()- objmap->GetScrollY() -128.0f;
		dst.m_left =  objhero->GetPosX()- objmap->GetScrollX()-128.0f;
		dst.m_right = dst.m_left + 300.0f;
		dst.m_bottom = dst.m_top + SIGN_SIZE*4.0f;
		//描画
		Draw::Draw(GRA_SIGN_FRAME, &src, &dst, color, 0.0f);
	}
}