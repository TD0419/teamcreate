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

//コンストラクタ
CObjWood::CObjWood(int x, int y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//イニシャライズ
void CObjWood::Init()
{
	
	
	// 角度変数初期化
	m_r = 0.0f;

	// 回転フラグ初期化
	m_rota_flag = false;

	//初期の木の画像の位置
	m_wood_x = m_px + (WOOD_SIZE - 64.0000f);
	m_wood_y = m_py;

	//当たり判定
	Hits::SetHitBox(this, m_wood_x, m_wood_y, 64, WOOD_SIZE, ELEMENT_GIMMICK, OBJ_WOOD, 1);
}

//アクション
void CObjWood::Action()
{	
	//主人公オブジェクト情報を持ってくる
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hero_x = objhero->GetPosX();
	float hero_y = objhero->GetPosY();
	float hero_vx = objhero->GetVecX();
	float hero_vy = objhero->GetVecY();

	// 回転フラグが立っていれば
	if (m_rota_flag == true)
	{
		//90度以上回転していれば
		if (m_r <= -90.0f)
		{
			//木の画像の位置を更新
			m_wood_x = m_px + WOOD_SIZE;
			m_wood_y = m_py + (WOOD_SIZE - 64.0000f);
			//主人公との当たり判定
			if (HeroHit(m_wood_x, m_wood_y, WOOD_SIZE, 64.0000f,
				&hero_x, &hero_y, HERO_SIZE_WIDTH, HERO_SIZE_HEIGHT, &hero_vx, &hero_vy)
				)
			{
				//主人公の位置を更新
				objhero->SetPosX(hero_x);
				objhero->SetPosY(hero_y);
				objhero->SetVecX(hero_vx);
				objhero->SetVecY(hero_vy);
			}
			
			//HitBoxの位置を更新する
			HitBoxUpData(Hits::GetHitBox(this), m_wood_x, m_wood_y, 64.0f, WOOD_SIZE);
			
			return;
		}
		else
		{
			//木の画像の位置更新
			m_wood_x = m_px + (WOOD_SIZE - 64.0000f);
			m_wood_y = m_py;
			//主人公との当たり判定
			if (HeroHit(m_wood_x, m_wood_y, 64.0000f, WOOD_SIZE,
				&hero_x, &hero_y, HERO_SIZE_WIDTH, HERO_SIZE_HEIGHT, &hero_vx, &hero_vy)
				)
			{
				//主人公の位置を更新
				objhero->SetPosX(hero_x);
				objhero->SetPosY(hero_y);
				objhero->SetVecX(hero_vx);
				objhero->SetVecY(hero_vy);
			}
			//木をまわす
			m_r -= 1.0f;
			HitBoxUpData(Hits::GetHitBox(this), m_wood_x, m_wood_y);
			return;
		}
	}
	else
	{
		//木の画像の位置更新
		m_wood_x = m_px + (WOOD_SIZE - 64.0000f);
		m_wood_y = m_py;
		//主人公との当たり判定
		if (int hit = HeroHit(m_wood_x, m_wood_y, 64.0000f, WOOD_SIZE,
			&hero_x, &hero_y, HERO_SIZE_WIDTH, HERO_SIZE_HEIGHT, &hero_vx, &hero_vy)
			)
		{
			//主人公の位置を更新
			objhero->SetPosX(hero_x);
			objhero->SetPosY(hero_y);
			objhero->SetVecX(hero_vx);
			objhero->SetVecY(hero_vy);
		}
		//HitBoxの位置を更新する
		HitBoxUpData(Hits::GetHitBox(this), m_wood_x, m_wood_y);
		return;
	}
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

//ブロックAとブロックBの当たり判定
//ブロックA＝移動しないブロック
//ブロックB＝あたった場合移動するブロック
//引数1  float  ax		:ブロックAのX位置
//引数2  float  ay		:ブロックAのY位置
//引数3  float  aw		:ブロックAの幅
//引数4  float  ah		:ブロックAの高さ
//引数5  float* bx		:ブロックBのX位置 ポインタ
//引数6  float* by		:ブロックBのY位置 ポインタ
//引数7  float  bw		:ブロックBの幅
//引数8  float  bh		:ブロックBの高さ
//引数9  float* bvx		:ブロックBのX移動量 ポインタ
//引数10 float* bvy		:ブロックBのY移動量 ポインタ
//戻り値	int			:当たったかどうか||どこに当たったか　0=当たり無し：1=Bから見て上：2=Bから見て下：3=Bから見て右:4=Bから見て左
int CObjWood::HeroHit(float ax,float ay,float aw,float ah,
						float* bx,float* by,float bw,float bh,
						float* bvx,float* bvy)
{
	float ax_min = ax;			//ブロックAのX座標最小
	float ay_min = ay;			//ブロックAのY座標最小
	float ax_max = ax_min + aw;	//ブロックAのX座標最大
	float ay_max = ay_min + ah;	//ブロックAのY座標最大

	float bx_min = *bx;			//ブロックBのX座標最小
	float by_min = *by;			//ブロックBのY座標最小
	float bx_max = bx_min + bw;	//ブロックBのX座標最大
	float by_max = by_min + bh;	//ブロックBのY座標最大

	//はみ出し許容範囲
	float bleed_x = 5.0f;
	float bleed_y = 20.0f;

	//当たり判定チェック
	if (ax_max < bx_min);//AよりBが右
	else if (bx_max < ax_min);//AよりBが左
	else if (ay_max < by_min);//AよりBが下
	else if (by_max < ay_min);//AよりBが上
	else	//当たりあり。
	{
		//ブロックAの上
		if (by_max - ay_min < bleed_y)
		{
			if(*bvy > 0.0f)
   				*bvy = 0.00000f;//Y移動量を0にする
			*by -= by_max - ay_min;
			return 2;
		}
		//ブロックAの下
		if (ay_max - by_min < bleed_y)
		{
   			if(*bvy < 0.0f)
				*bvy = 0.00000f;//Y移動量を0にする
			*by += ay_max - by_min;
			return 1;
		}
		//ブロックAの左
		if (bx_max - ax_min < bleed_x)
		{
			if(*bvx > 0.0f)
				*bvx = 0.00000f;//X移動量を0にする
			*bx -= bx_max - ax_min;
			return 3;
		}
		//ブロックAの右
		if (ax_max - bx_min < bleed_x)
		{
			if(*bvx < 0.0f)
				*bvx = 0.00000f;//X移動量を0にする
			*bx += ax_max - bx_min;
			return 4;
		}
	}
	return 0;
}
