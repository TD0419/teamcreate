#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjLiftMove.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjLiftMove::CObjLiftMove(int x, int y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//イニシャライズ
void CObjLiftMove::Init()
{
	m_vx = 1.0f;
	m_vy = 0.0f;

	//当たり判定
	Hits::SetHitBox(this, m_px, m_py, LIFT_MOVE_SIZE_WIDTH, LIFT_MOVE_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_LIFT_MOVE, 1);

}

//アクション
void CObjLiftMove::Action()
{
	//自身のHitBoxをもってくる
	CHitBox*hit = Hits::GetHitBox(this);

	//主人公が当たっていれば
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		HeroRide();//主人公を乗せる処理をする
	}

	//----------------バグあるので次の時間にやる

	////マップオブジェクトを持ってくる
	//CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//int map_num = objmap->GetMap((m_px + LIFT_MOVE_SIZE_WIDTH), m_map_y + 1);
	//int map_num2 = objmap->GetMap(m_map_x-1, m_map_y + 1 );

	////左右に動く        
	//if (map_num == MAP_BLOCK) //m_timeが520より下なら右に動く
	//{
	//	m_vx =  -1.0f;
	//}
	//else if (map_num2 == MAP_BLOCK)
	//{
 //		m_vx =   1.0f;
	//}
	//


	//移動
	m_px += m_vx;
	m_py += m_vy;

	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//ドロー
void CObjLiftMove::Draw()
{
}

//主人公を乗せる処理をする
void CObjLiftMove::HeroRide()
{
	//自身のHitBoxをもってくる
	CHitBox*hit = Hits::GetHitBox(this);

	HIT_DATA** hit_data;	//衝突の情報を入れる構造体
	hit_data = hit->SearchObjNameHit(OBJ_HERO);//衝突の情報をhit_dataに入れる

	for (int i = 0; i < hit->GetCount(); i++)
	{
		if (hit_data[i] != nullptr)
		{
			float r = hit_data[i]->r;//あたっている角度を持ってくる

									 //上側があたっていればで
			if (45.0f <= r && r <= 135.0f)
			{
				//主人公オブジェクトを持ってくる
				CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);
				float h_px = objhero->GetPosX();//主人公の位置Xを持ってくる

				objhero->SetHitDown(true);//リフトの上に主人公が乗っていたらm_hit_downにtrueを返す

										  //リフトに乗せる処理
				objhero->SetVecY(0.0f);//主人公のY方向の移動を０にする
				objhero->SetPosX(h_px + m_vx);//主人公の位置をもともと主人公が居た位置＋リフトの移動量にする
				objhero->SetPosY(m_py - HERO_SIZE_HEIGHT + 1.0f);//主人公のポジションをリフトの上にする
			}
		}
	}
}