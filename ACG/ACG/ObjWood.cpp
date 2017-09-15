#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjWood.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;
bool UnitVec(float* vx, float* vy);
//コンストラクタ
CObjWood::CObjWood(int x, int y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//イニシャライズ
void CObjWood::Init()
{
	m_r = 0.0f;
	//当たり判定
	Hits::SetHitBox(this, m_px, m_py, WOOD_SIZE, WOOD_SIZE, ELEMENT_GIMMICK, OBJ_WOOD, 1);
	
	// 角度変数初期化
	m_r  = 0.0f;
}

//アクション
void CObjWood::Action()
{	
	//90度以上回転していれば
	if (m_r <= -90.0f)
	{
		HeroHit(m_px + WOOD_SIZE, m_py);//主人公との当たり判定
	
		//HitBoxの位置を更新する
		HitBoxUpData(Hits::GetHitBox(this), m_px + WOOD_SIZE, m_py);
		return;
	}
	else
	{
		HeroHit(m_px, m_py);//主人公との当たり判定
		//木をまわす
		m_r -= 1.0f;

		//HitBoxの位置を更新する
		HitBoxUpData(Hits::GetHitBox(this), m_px , m_py);
	}

	
}

//ドロー
void CObjWood::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//描画位置
	dst.m_top = 0.0f + m_py - obj_m->GetScrollY();
	dst.m_left = 0.0f + m_px - obj_m->GetScrollX();
	dst.m_right = dst.m_left + WOOD_SIZE;
	dst.m_bottom = dst.m_top + WOOD_SIZE;

	//描画
	Draw::Draw(7, &src, &dst, color, m_r,-1.0f,-1.0f);
}

//主人公が触れたときの処理
//引数1,2 木のポジション
void CObjWood::HeroHit(float px, float py)
{
	//自身のHitBoxをもってくる
	CHitBox*hit = Hits::GetHitBox(this);

	HIT_DATA** hit_data;	//衝突の情報を入れる構造体
	hit_data = hit->SearchObjNameHit(OBJ_HERO);//衝突の情報をhit_dataに入れる

											   //主人公オブジェクトを持ってくる
	CObjHero* obj_hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	for (int i = 0; i < hit->GetCount(); i++)
	{
		//データがあれば
		if (hit_data[i] != nullptr)
		{
			float r = hit_data[i]->r;//あたっている角度をもってくる

			//ブロックの右側が衝突している場合
			if (0 < r && r < 45 || 315 < r && r < 360)
			{
				obj_hero->SetVecX(0.0f);//主人公のX方向の移動を０にする
				obj_hero->SetPosX(px + WOOD_SIZE);//主人公の位置を木の右側までずらす
			}
			//ブロックの上側が衝突している場合
			else if (45 < r && r < 125)
			{

				obj_hero->SetVecY(0.0f);//主人公のY方向の移動を０にする
				obj_hero->SetPosY(py - HERO_SIZE_HEIGHT);//主人公の位置を木の上側までずらす
			}
			//ブロックの左側が衝突している場合
			else if (125 < r && r < 225)
			{
				obj_hero->SetVecX(0.0f);//主人公のX方向の移動を０にする
				obj_hero->SetPosX(px - HERO_SIZE_WIDTH);//主人公の位置を木の左側までずらす
			}
			//ブロックの下側が衝突している場合
			else if (225 < r && r < 315)
			{
				obj_hero->SetVecY(0.0f);//主人公のY方向の移動を０にする
				obj_hero->SetPosY(py + WOOD_SIZE);//主人公の位置を木の下側までずらす
			}
		}
	}
}
