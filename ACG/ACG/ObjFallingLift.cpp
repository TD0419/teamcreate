//使用するヘッダーファイル　
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjFallingLift.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjFallingLift::CObjFallingLift(int x, int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
}

//イニシャライズ
void CObjFallingLift::Init()
{
	m_get_on_flag = false;		//false…主人公が乗っていない  true…主人公が乗っている
	//当たり判定用HitBoxを作成                          
	Hits::SetHitBox(this, m_px, m_py, ROLL_BLOCK_SIZE_WIDTH, ROLL_BLOCK_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_FALLING_LIFT, 1);
}

//アクション
void CObjFallingLift::Action()
{
	//HitBoxのポインタを持ってくる
	CHitBox*hit = Hits::GetHitBox(this);

	//主人公があたっている&&主人公がリフトの上に立ってないとき
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr&&m_get_on_flag == false)
	{
		HeroRide();//衝突処理をする
	}
	//主人公があたっている&&主人公がリフトの上に立ってる時
	else if (hit->CheckObjNameHit(OBJ_HERO) != nullptr&&m_get_on_flag == true)
	{
		m_py += 5.0f;	//落ちるリフトが移動(落下する)
		HeroRide();//衝突処理をする
	}

	//HitBoxの位置を更新する
	HitBoxUpData(hit, m_px, m_py);
}

//ドロー
void CObjFallingLift::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = ROLL_BLOCK_SIZE_WIDTH;
	src.m_bottom = ROLL_BLOCK_SIZE_HEIGHT;

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + ROLL_BLOCK_SIZE_WIDTH;
	dst.m_bottom = dst.m_top + ROLL_BLOCK_SIZE_HEIGHT;
		
	//描画
	Draw::Draw(GRA_FALLING_LIFT, &src, &dst, color, 0.0f);
}

//主人公が当たったときの処理
void CObjFallingLift::HeroRide()
{
	//主人公オブジェクトを持ってくる
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//自身のHitBoxをもってくる
	CHitBox*hit = Hits::GetHitBox(this);

	HIT_DATA** hit_data;										//衝突の情報を入れる構造体
	hit_data = hit->SearchObjNameHit(OBJ_HERO);					//衝突の情報をhit_dataに入れる

	for (int i = 0; i < hit->GetCount(); i++)
	{
		if (hit_data[i] != nullptr)								//ヒットデータがあれば
		{
			float r = hit_data[i]->r;							//あたっている角度を持ってくる

			//上側があたっていれば
			if (31.0f < r && r < 145.5f)
			{
				m_get_on_flag = true;							//「主人公が乗っている」と識別する。
				objhero->SetHitDown(true);						//主人公が乗っていたらm_hit_downにtrueを返す
			    //乗せる処理
				objhero->SetPosY(m_py - HERO_SIZE_HEIGHT + 2.5f);//主人公のポジションをリフトの上にする
				objhero->SetVecY(4.0f);							//主人公のY方向の移動を3にする
			}
			//左側が当たっていれば
			if (145.5f <= r && r <= 210.0f)
			{
				m_get_on_flag = false;							//「主人公は乗っていない」と識別する。
				//主人公が右側向いているとき
				if (objhero->GetPosture() == 0.0f)
				{
					//左に反発する処理
					objhero->SetPosX(m_px - 49.0f);	//主人公の位置をブロックの左にする
					objhero->SetVecX(0.0f);//主人公のX方向の移動を０にする
				}
				//主人公が左向いている時
				else
				{
					//左に反発する処理
					objhero->SetPosX(m_px - 62.0f);	//主人公の位置をブロックの左にする
					objhero->SetVecX(0.0f);//主人公のX方向の移動を０にする
				}
			}
			//右側が当たっていれば
			if (0.0f <= r && r <= 31.0f||335.0f<r&&r<360.0f )
			{
				if (objhero->GetPosture() == 1.0f)
				{
					m_get_on_flag = false;//「主人公は乗っていない」と識別する。
					//右に反発する処理
					objhero->SetPosX(m_px + 177.0f);//主人公の位置をブロックの右にする
					objhero->SetVecX(0.0f);//主人公のX方向の移動を０にする
				}
				else
				{
					m_get_on_flag = false;//「主人公は乗っていない」と識別する。
					//右に反発する処理
					objhero->SetPosX(m_px + 190.0f);	//主人公の位置をブロックの右にする
					objhero->SetVecX(0.0f);//主人公のX方向の移動を０にする
				}
			}
			
			//下側があたっていれば
			if (210.0f < r && r < 335.0f)
			{
				m_get_on_flag = false;							//「主人公は乗っていない」と識別する。
				//下に反発する処理
				objhero->SetPosY(m_py + 49.5f);//主人公の位置をブロックの下にする
				objhero->SetVecY(0.0f);//主人公のY方向の移動を０にする
			}
		}
	}
}