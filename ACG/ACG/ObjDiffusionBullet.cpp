#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjDiffusionBullet.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ(砲台用)
CObjDiffusionBullet::CObjDiffusionBullet(float x, float y, int r)
{
	m_px = x ;
	m_py = y ;
	m_r  = (float)r;
	m_type = CANNON;
	m_speed = 5.5f;

}

//コンストラクタ(ボス用)
CObjDiffusionBullet::CObjDiffusionBullet(float x, float y, int r, CObjDiffusionSource* p)
{
	m_px = x;
	m_py = y;
	m_r = (float)r;
	m_type = BOSS;
	mp_base = p;
	m_speed = 3.0f;
}

//イニシャライズ
void CObjDiffusionBullet::Init()
{
	//飛んでいく方向の計算
	m_vx = cos(3.14f / 180.0f*m_r);
	m_vy = sin(3.14f / 180.0f*m_r);
	
	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 16.0f, 16.0f, ELEMENT_ENEMY, OBJ_DIFFUSION_BULLET, 1);
}

//アクション
void CObjDiffusionBullet::Action()
{
	//移動
	m_px += m_vx * m_speed;
	m_py -= m_vy * m_speed;

	//画面外なら
	if( WindowCheck(m_px, m_py, BULLET_SIZE, BULLET_SIZE) == false )
	{
		switch (m_type)
		{
			case CANNON:
			{
				//主人公と拡散砲台のオブジェクトをもってくる
				CObjDiffusionCannon* objcannon = (CObjDiffusionCannon*)Objs::GetObj(OBJ_DIFFUSION_CANNON);
				CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

				if (objcannon != nullptr)//砲台があれば
				{
					//主人公と拡散砲台のYの位置を持ってくる
					float cannon_y = objcannon->GetPosY();
					float hero_y = objhero->GetPosY();

					//拡散砲台と弾の距離　が　拡散砲台とヒーローの距離　より大きければ
					if (abs(cannon_y - m_py) > abs(cannon_y - hero_y))
					{
						WindowOutDelete(this);//削除処理
						return;
					}
				}
				else	//砲台がなければ
				{
					WindowOutDelete(this);//削除処理
					return;
				}
				break;
			}
			case BOSS:
			{
				//主人公のオブジェクトをもってくる
				CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

				//主人公と打ち出し源の位置Yを持ってくる
				float base_y = mp_base->GetPosY();
				float hero_y = objhero->GetPosY();

				//拡散砲台と弾の距離　が　拡散砲台とヒーローの距離　より大きければ
				if (abs(base_y - m_py) > abs(base_y - hero_y))
				{
					WindowOutDelete(this);//削除処理
					return;
				}
				break;
			}
		}
	}

	//拡散弾HitBox更新用ポインター取得
	CHitBox* hit = Hits::GetHitBox(this);

	//Heroに当たれば削除
	if ( DeleteCheckObjNameHit (hit, this, OBJ_HERO))
		return;

	// ブロックオブジェクトを持ってくる
	CObjBlock* objblock = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//ブロックとの当たり判定
	objblock->AllBlockHit(&m_px, &m_py, BULLET_SIZE, BULLET_SIZE,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy);

	//ブロックとあたっていれば削除する
	if (m_hit_up == true || m_hit_down == true || m_hit_right == true || m_hit_left == true)
	{
		this->SetStatus(false);		//自身に消去命令を出す。
		Hits::DeleteHitBox(this);	//弾丸が所持するHitBoxを除去。
		return;
	}

	//主人公とあたったら消去
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		this->SetStatus(false);		//自身に消去命令を出す。
		Hits::DeleteHitBox(this);	//弾丸が所持するHitBoxを除去。
		return;
	}
	//落ちるブロックと当たったら消去
	if (DeleteCheckObjNameHit(hit, this, OBJ_FALLING_BLOCK))
	{
		return;
	}

	//HitBoxの位置を更新する
	HitBoxUpData(hit, m_px, m_py);
}

//ドロー
void CObjDiffusionBullet::Draw()
{
	// マップ情報を持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };
	RECT_F src, dst;

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 16.0f;
	src.m_bottom = 16.0f;

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + 16.0f;
	dst.m_bottom = dst.m_top + 16.0f;

	if (m_type == CANNON)
		Draw::Draw(GRA_CANNON_BEAM, &src, &dst, color, m_r);
	
	if (m_type == BOSS)
		Draw::Draw(GRA_BOSS_DIFFUSION, &src, &dst, color, m_r);
}