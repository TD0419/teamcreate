#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjWood.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjWood::CObjWood(int x, int y)
{
	m_px = x * WOOD_SIZE_WIDTH;
	m_py = y * WOOD_SIZE_HEIGHT;
}

//イニシャライズ
void CObjWood::Init()
{
	//当たり判定
	Hits::SetHitBox(this, m_px, m_py, WOOD_SIZE_WIDTH, WOOD_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_WOOD, 1);

}

//アクション
void CObjWood::Action()
{
	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
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
				obj_hero->SetPosX(m_px + WOOD_SIZE_WIDTH);//主人公の位置を木の右側までずらす
			}
			//ブロックの上側が衝突している場合
			else if (45 < r && r < 125)
			{

				obj_hero->SetVecY(0.0f);//主人公のY方向の移動を０にする
				obj_hero->SetPosY(m_py - HERO_SIZE_HEIGHT);//主人公の位置を木の上側までずらす
			}
			//ブロックの左側が衝突している場合
			else if (125 < r && r < 225)
			{
				obj_hero->SetVecX(0.0f);//主人公のX方向の移動を０にする
				obj_hero->SetPosX(m_px - HERO_SIZE_WIDTH);//主人公の位置を木の左側までずらす
			}
			//ブロックの下側が衝突している場合
			else if (225 < r && r < 315)
			{
				obj_hero->SetVecY(0.0f);//主人公のY方向の移動を０にする
				obj_hero->SetPosY(m_py + WOOD_SIZE_HEIGHT);//主人公の位置を木の下側までずらす
			}
		}
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
	dst.m_right = dst.m_left + WOOD_SIZE_WIDTH;
	dst.m_bottom = dst.m_top + WOOD_SIZE_HEIGHT;

	//描画
	Draw::Draw(7, &src, &dst, color, 0);
}