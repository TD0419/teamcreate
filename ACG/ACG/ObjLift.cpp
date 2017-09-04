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
	m_vx = 1.0f;
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

	float r = hit_data[0]->r;//あたっている角度を持ってくる

	//上側があたっていればで
	if (45.0f <= r && r <= 135.0f)
	{
		//主人公オブジェクトを持ってくる
		CObjHero* obj_hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
		float h_px = obj_hero->GetPosX();//主人公の位置Xを持ってくる

		//リフトに乗せる処理
		obj_hero->SetPosX(h_px + m_vx);//主人公の位置をもともと主人公が居た位置＋リフトの移動量にする
		obj_hero->SetPosY(m_py - HERO_SIZE_Y);//主人公のポジションをリフトの上にする
	}
}