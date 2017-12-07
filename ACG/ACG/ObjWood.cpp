#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjWood.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjWood::CObjWood(int x, int y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;

	//マップ情報の木の位置が木の下を指していたので調整
	m_px -= WOOD_SIZE - 64.0f;
	m_py -= WOOD_SIZE - 64.0f;

	m_map_x = x;
	m_map_y = y;
}

//イニシャライズ
void CObjWood::Init()
{	
	// 角度変数初期化
	m_r = 0.0f;

	//初期の木の画像の位置
	m_wood_image_x = m_px + (WOOD_SIZE - 64.0000f);
	m_wood_image_y = m_py;
	m_audio_start_flag = false;//木の音を鳴らすフラグ

	//当たり判定
	Hits::SetHitBox(this, m_wood_image_x, m_wood_image_y, 64, WOOD_SIZE, ELEMENT_GIMMICK, OBJ_WOOD, 1);
}

//アクション
void CObjWood::Action()
{	
	//画面外なら
	if (WindowCheck(m_px, m_py, 64.0f, WOOD_SIZE) == false)
	{
		WindowOutDelete(this, m_map_x, m_map_y);//削除処理(復活あり)
		return;
	}

	//主人公オブジェクト情報を持ってくる
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hero_x = objhero->GetPosX();
	float hero_y = objhero->GetPosY();
	float hero_vx = objhero->GetVecX();
	float hero_vy = objhero->GetVecY();

	//HitBoxの幅、高さ
	float hit_w, hit_h;

	//90度以上回転していれば
	if (m_r <= -90.0f)
	{
		//木の画像の位置を更新
		m_wood_image_x = m_px + WOOD_SIZE;
		m_wood_image_y = m_py + (WOOD_SIZE - 64.0000f);

		//HitBoxの幅、高さ設定
		hit_w = WOOD_SIZE;
		hit_h = 64.0f;
	}
	else
	{
		CObjLeverSwich* objlever_swich = (CObjLeverSwich*)Objs::GetObj(OBJ_LEVER_SWICH);
		
		// レバースイッチがあれば
		if (objlever_swich != nullptr)
		{
			// 回転フラグが立っていれば
			if (objlever_swich->GetWood() == true)
			{
				if (m_audio_start_flag == false)
				{
					Audio::Start(TREE);
					m_audio_start_flag = true;
				}
				m_r -= 1.0f;//木をまわす
			}
		}
		//木の画像の位置更新
		m_wood_image_x = m_px + (WOOD_SIZE - 64.0000f);
		m_wood_image_y = m_py;

		//HitBoxの幅、高さ設定
		hit_w = 64.0f;
		hit_h = WOOD_SIZE;
	}

	//主人公との当たり判定
	//衝突したら主人公の位置を更新する
	if (HitTestOfAB(m_wood_image_x, m_wood_image_y, hit_w, hit_h,
		&hero_x, &hero_y, 42, 120, &hero_vx, &hero_vy)
		)
	{
		//主人公の位置を更新
		objhero->SetPosX(hero_x);
		objhero->SetPosY(hero_y+2.0f);
		objhero->SetVecX(hero_vx);
		objhero->SetVecY(hero_vy);
	}

	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_wood_image_x, m_wood_image_y, hit_w, hit_h);	
}

//ドロー
void CObjWood::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	//左に木を持っていきたいので左右反転させる
	src.m_top = 0.0f;
	src.m_left = 320.0f;
	src.m_right = 0.0f;
	src.m_bottom = 320.0f;

	//描画位置
	dst.m_top = 0.0f + m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + WOOD_SIZE;
	dst.m_bottom = dst.m_top + WOOD_SIZE;

	//描画
	Draw::Draw(GRA_WOOD, &src, &dst, color, m_r,-1.0f,-1.0f);
}
