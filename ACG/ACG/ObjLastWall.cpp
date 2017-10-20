#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjLastWall.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjLastWall::CObjLastWall(int x, int y)
{
	m_px = (float)x * 64.0f;
	m_py = (float)y * 64.0f;
}

//イニシャライズ
void CObjLastWall::Init()
{
	m_ani_time = 0;
	m_ani_frame = 1;  //静止フレームを初期にする
	m_ani_max_time = 17.0f; //アニメーション間隔幅
	m_ani_start = false;

	m_wall_gauge = 0;
	GateOpenflag = false;
	//当たり判定																
	Hits::SetHitBox(this, m_px, m_py, 32, 512, ELEMENT_GIMMICK, OBJ_LAST_WALL, 1);
}

//アクション
void CObjLastWall::Action()
{
	m_ani_time += 4;

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);

	// m_wall_gaugeが512を越えたら処理ストップ
	if (GateOpenflag == true)
	{
		if (m_wall_gauge >= 512)
		{
			Hits::DeleteHitBox(this);//hitbox削除

			return;
		}
		else
		{
			m_wall_gauge += 1; // 1ずつ増やしていく
								   // hitboxが小さくなる
			hit->SetPos(m_px, m_py + m_wall_gauge, 512 - m_wall_gauge, 32);

			////アニメーションの感覚管理
			//if (m_ani_time > m_ani_max_time)
			//{
			//	m_ani_frame += 1;
			//	m_ani_time = 0;
			//}

			////最後までアニメーションが進むと最初に戻る
			//if (m_ani_frame == 2)
			//{
			//	m_ani_frame = 0;
			//}
		}
	}
	HIT_DATA** hit_data;	//衝突の情報を入れる構造体
	hit_data = hit->SearchObjNameHit(OBJ_HERO);//衝突の情報をhit_dataに入れる

											   //主人公オブジェクトを持ってくる
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);


	for (int i = 0; i < hit->GetCount(); i++)
	{
		//データがあれば
		if (hit_data[i] != nullptr)
		{
			float r = hit_data[i]->r;//あたっている角度をもってくる

									 //LastWallの右側が衝突している場合
			if (0 < r && r < 85 || 275 < r && r < 360)
			{
				objhero->SetVecX(0.0f);//主人公のX方向の移動を０にする
				objhero->SetPosX(m_px + 62.0f);//主人公の位置をLastWallの右側までずらす
			}

			//LastWallの上側が衝突している場合
			else if (85 < r && r < 94)
			{

				objhero->SetVecY(0.0f);//主人公のY方向の移動を０にする
				objhero->SetPosY(m_py+68.0f);//主人公の位置をLastWallの上側までずらす

			}

			//LastWallの左側が衝突している場合
			else if (94 < r && r < 266)
			{
				objhero->SetVecX(0.0f);//主人公のX方向の移動を０にする
				objhero->SetPosX(m_px - HERO_SIZE_WIDTH+28.0f);//主人公の位置をLastWallの左側までずらす
			}

			//LastWallの下側が衝突している場合
			else if (266 < r && r < 275)
			{
				objhero->SetVecY(0.0f);//主人公のY方向の移動を０にする
				objhero->SetPosY(m_py + 512.0f);//主人公の位置をLastWallの下側までずらす
			}
		}
	}
	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px+29, m_py+195);
}

//ドロー
void CObjLastWall::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 256.0f;

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY() - 60;
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + 96.0f;
	dst.m_bottom = dst.m_top + 256.0f;

	//描画(上の部分)
	Draw::Draw(21, &src, &dst, color, 0.0f);

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 512.0f;

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY() + 195;
	dst.m_left = m_px - objmap->GetScrollX() + 30;
	dst.m_right = dst.m_left + 32;
	dst.m_bottom = dst.m_top + 512-m_wall_gauge;
	//描画(下の部分)
	Draw::Draw(22, &src, &dst, color, 0.0f);
}