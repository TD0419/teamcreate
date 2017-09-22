#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjLift.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjLift::CObjLift(int x, int y)
{
	m_px = x * LIFT_SIZE;
	m_py = y * LIFT_SIZE;
}

//イニシャライズ
void CObjLift::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;

	//当たり判定
	Hits::SetHitBox(this, m_px, m_py, LIFT_SIZE, LIFT_SIZE, ELEMENT_GIMMICK, OBJ_LIFT, 1);

}

//アクション
void CObjLift::Action()
{
	//自身のHitBoxをもってくる
	CHitBox*hit = Hits::GetHitBox(this);

	//移動
	m_px += m_vx;
	m_py += m_vy;

	//主人公が当たっていれば
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		HeroRide();//主人公を乗せる処理をする
	}

	//ロープオブジェクトを持ってくる
	CObjRopeSwitch* objrope_switch = (CObjRopeSwitch*)Objs::GetObj(OBJ_ROPE_SWITCH);
	
	if (objrope_switch->GetRopeFlag() == true)//ロープとロープスイッチがあたっているとき
	{
		m_vx = -1.0f;
	}
	else//ロープとロープスイッチがあたっていないとき
	{
		m_vx = 1.0f;
	}

	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//ドロー
void CObjLift::Draw()
{
	
}

//主人公を乗せる処理をする
void CObjLift::HeroRide()
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
				objhero->SetPosX(h_px + m_vx);//主人公の位置をもともと主人公が居た位置＋リフトの移動量にする
				objhero->SetPosY(m_py - HERO_SIZE_HEIGHT);//主人公のポジションをリフトの上にする
			}
		}
	}
}