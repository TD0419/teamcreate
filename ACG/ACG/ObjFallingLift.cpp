//使用するヘッダーファイル　
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
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
	//当たり判定用HitBoxを作成                          
	Hits::SetHitBox(this, m_px, m_py, ROLL_BLOCK_SIZE_WIDTH, ROLL_BLOCK_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_FALLING_LIFT, 1);
}

//アクション
void CObjFallingLift::Action()
{
	//HitBoxのポインタを持ってくる
	CHitBox*hit = Hits::GetHitBox(this);

	//ヒーローオブジェクトと当たっていれば
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		HeroRide();//衝突処理をするをする
	}
	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
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
	Draw::Draw(GRA_ROLL_BLOCK, &src, &dst, color, 0);
	
	
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
			if (35.0f < r && r < 145.0f)
			{
				objhero->SetHitDown(true);						//主人公が乗っていたらm_hit_downにtrueを返す
			    //乗せる処理
				objhero->SetPosY(m_py - 126.0f);				//ブロックの上側に調節する

				//主人公の移動ベクトルが下向きなら
				if (objhero->GetVecY()>1.0f)
					objhero->SetVecY(1.0f);						//主人公のY方向の移動を0にする
			}
			//左側が当たっていれば
			else if (145.0f <= r && r <= 180.0f)
			{
				//左に反発する処理
				objhero->SetPosX(m_px - HERO_SIZE_WIDTH+0.8f);	//主人公の位置をブロックの左にする
				objhero->SetVecX(-1.0f * objhero->GetVecX());	//主人公のX方向の移動量を反転する
			}
			//右側が当たっていれば
			else if (0.0f <= r && r <= 35.0f )
			{
				//右に反発する処理
				objhero->SetPosX(m_px + ROLL_BLOCK_SIZE_WIDTH);	//主人公の位置をブロックの右にする
				objhero->SetVecX(-1.0f * objhero->GetVecX());	//主人公のX方向の移動量を反転する
			}

			//下側があたっていれば
			else if (180.0f < r && r < 360.0f)
			{
				//下に反発する処理
				objhero->SetPosY(m_py + ROLL_BLOCK_SIZE_HEIGHT);//主人公の位置をブロックの下にする
				objhero->SetVecY(-1.0f * objhero->GetVecY());	//主人公のY方向の移動量を反転する
			}
		}
	}
}