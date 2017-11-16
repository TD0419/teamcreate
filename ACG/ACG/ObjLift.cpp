#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"
#include "ObjLift.h"
#include "Function.h"
#include <math.h>

//使用するネームスペース
using namespace GameL;

//コンストラクタ(移動のベクトルつき）
//引数1,2	マップの数値(位置)
//引数3,4	移動するときの速度
//引数5		移動の最大量（左右）
//引数6		移動の最大量（上下）
//引数		移動のためのフラグの配列の要素数	＊後に改造するのでこのままおいといてください
CObjLift::CObjLift(int px, int py,float vx,float vy,float width_max, float length_max)
{
	//表示すべき位置を入れる
	m_px = (float)px * BLOCK_SIZE;	
	m_py = (float)py * BLOCK_SIZE;
	
	//移動ベクトルを入れる
	m_vx = vx;
	m_vy = vy;

	//移動の最大量を入れる
	m_width_max = width_max;	
	m_length_max = length_max;
}

//コンストラクタ
CObjLift::CObjLift(int px,int py)
{
	m_px = (float)px * BLOCK_SIZE;
	m_py = (float)py * BLOCK_SIZE;
	m_vx = 0.0f;
	m_vy = 0.0f;

}

//イニシャライズ
void CObjLift::Init()
{
	m_move_x = 0.0f;
	m_move_y = 0.0f;

	//当たり判定
	Hits::SetHitBox(this, m_px, m_py, LIFT_SIZE_WIDTH, LIFT_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_LIFT, 1);

}

//アクション
void CObjLift::Action()
{
	//自身のHitBoxをもってくる
	CHitBox*hit = Hits::GetHitBox(this);

	//主人公が当たっていれば
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		HeroRide();//主人公を乗せる処理をする
	}

	//ロープオブジェクトを持ってくる
	CObjRopeSwitch* objrope_switch = (CObjRopeSwitch*)Objs::GetObj(OBJ_ROPE_SWITCH);
	
	//専用的過ぎてパターンわけが必要なのでとりあえずコメント化しています
	//if (objrope_switch->GetRopeFlag() == true)//ロープとロープスイッチがあたっているとき
	//{
	//	if (Input::GetVKey('A'))
	//		m_vx = -1.0f;
	//	else
	//		m_vx = 0.0f;
	//}
	//else//ロープとロープスイッチがあたっていないとき
	//{
	//	m_vx = 1.0f;
	//}

	//左右の移動量調整
	if (m_move_x > m_width_max)	//移動量が最大量を超えると
	{
		m_vx *= (-1);	//移動方向を反転して
		m_move_x = 0.0f;//移動量の初期化
	}

	//上下の移動量調整
	if (m_move_y > m_length_max)	//移動量が最大量を超えると
	{
		m_vy *= (-1);	//移動方向を反転して
		m_move_y = 0.0f;//移動量の初期化
	}	

	//移動
	m_px += m_vx;
	m_py += m_vy;

	//移動量の保存
	m_move_x += abs(m_vx);
	m_move_y += abs(m_vy);

	//HitBoxの位置を更新する
	HitBoxUpData(hit, m_px, m_py);
}

//ドロー
void CObjLift::Draw()
{	
	//mapオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//描画色を決める
	float color[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src, dst;

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 128.0f;
	src.m_bottom = 128.0f;

	//描画の位置
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + LIFT_SIZE_WIDTH;
	dst.m_bottom = dst.m_top + LIFT_SIZE_HEIGHT;

	//リフトの描画
	Draw::Draw(GRA_LIFT, &src, &dst, color, 0.0f);
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
				objhero->SetVecY(0.0f);//主人公のY方向の移動を0にする
				objhero->SetPosX(h_px + m_vx);//主人公の位置をもともと主人公が居た位置＋リフトの移動量にする
				objhero->SetPosY(m_py - HERO_SIZE_HEIGHT+1.0f);//主人公のポジションをリフトの上にする
			}
		}
	}
}