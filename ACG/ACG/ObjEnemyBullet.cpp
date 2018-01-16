#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjEnemyBullet.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ（BOSS用主人公の方向へ）
CObjEnemyBullet::CObjEnemyBullet(float x, float y)
{
	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//初期位置を決める
	m_px = x;
	m_py = y;
	
	//速さを決める
	m_speed = 6.5f;

	//敵用弾丸にスクロールの影響を適用させる
	x -= objmap->GetScrollX();
	y -= objmap->GetScrollY();

	//主人公との角度の計算を行う-----------------------------
	//主人公のオブジェクト情報を持ってくる
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hero_x = objhero->GetPosX() - objmap->GetScrollX();		//主人公の位置情報X取得
	float hero_y = objhero->GetPosY() - objmap->GetScrollY();		//主人公の位置情報Y取得

	//主人公の位置ベクトル情報取得
	float Hvector_x = hero_x - x;
	float Hvector_y = hero_y - y;

	//斜辺取得
	float hypotenuse = sqrt(Hvector_y * Hvector_y + Hvector_x * Hvector_x);

	//角度を求める
	m_r = acosf(Hvector_x / hypotenuse);
	//----------------------------------------------------------

	//角度方向に弾丸を移動させる
	m_vx = cosf(m_r) * m_speed;
	m_r = m_r * 180.0f / 3.14f;

	//主人公のY位置が上だった場合の発射角度
	if (hero_y > y)
	{
		//180°～360°の値にする
		m_r = 360 - abs(m_r);
	}
	//主人公のY位置が下だった場合の発射角度
	if (hero_y < y)
	{
		m_vy = -sin(acosf(Hvector_x / hypotenuse)) * m_speed;
	}
	else
	{
		m_vy = sin(acosf(Hvector_x / hypotenuse)) * m_speed;
	}
}

//コンストラクタ(ギミック用　指定した方向へ)
CObjEnemyBullet::CObjEnemyBullet(float x, float y, float rad)
{
	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//初期位置を決める
	m_px = x;
	m_py = y;
	m_r = rad;

	//速さを決める
	m_speed = 6.5f;

	//敵用弾丸にスクロールの影響を適用させる
	x -= objmap->GetScrollX();
	y -= objmap->GetScrollY();
}

//イニシャライズ
void CObjEnemyBullet::Init()
{
	m_delete_flag = false;

	m_hit_up = false;
	m_hit_right = false;
	m_hit_left = false;
	m_hit_down = false;
	
	switch (((UserData*)Save::GetData())->stagenum)
	{
		case 5://ステージ５
		{
			//当たり判定用HitBoxを作成
			Hits::SetHitBox(this, m_px, m_py, STAGE5_BOSS_BULLET_SIZE, STAGE5_BOSS_BULLET_SIZE, ELEMENT_ENEMY, OBJ_ENEMY_BULLET, 1);
			break;
		}
		default:
		{
			//当たり判定用HitBoxを作成
			Hits::SetHitBox(this, m_px, m_py, BULLET_SIZE, BULLET_SIZE, ELEMENT_ENEMY, OBJ_ENEMY_BULLET, 1);
			break;
		}
	}

}

//アクション
void CObjEnemyBullet::Action()
{
	//移動
	m_px += m_vx*1.0f;
	m_py += m_vy*1.0f;

	//画面外なら
	if(WindowCheck(m_px, m_py, BULLET_SIZE, BULLET_SIZE)==false)
	{
		switch ((((UserData*)Save::GetData())->stagenum))
		{
			case 2:	//ステージ2(ボス)
			{
				//主人公とボスのオブジェクトをもってくる
				CObjBoss* objboss = (CObjBoss*)Objs::GetObj(OBJ_BOSS);
				CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

				//主人公とボスのXの位置を持ってくる(死亡していないとき)
				float boss_x = 0.f; 
				if (objboss != nullptr)
				{
					objboss->GetPosX();
				}
				
				float hero_x = objhero->GetPosX();

				//ボスと弾の距離　が　ボスとヒーローの距離　より大きければ
				if (abs(boss_x - m_px) > abs(boss_x - hero_x))
					m_delete_flag = true;//削除フラグをオンにする

				break;
			}
			case 3:	//ステージ3
			{
				CObjStage5Boss* objboss5 = (CObjStage5Boss*)Objs::GetObj(OBJ_STAGE5_BOSS);
				CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

				//主人公とボス5のXの位置を持ってくる(死亡していないとき)
				float boss_y = 0.f;
				if (objboss5!=nullptr)
				{
					objboss5->GetPosY();
				}
					
				float hero_y = objhero->GetPosY();

				//ボスと弾の距離　が　ボスとヒーローの距離　より大きければ
				if (abs(boss_y - m_py) > abs(boss_y - hero_y))
					m_delete_flag = true;//削除フラグをオンにする

				break;
			}
		}
	}

	if (m_delete_flag == true)	//削除フラグがオンなら
	{
		WindowOutDelete(this);//削除処理
		return;
	}
	
	//ブロックオブジェクトを持ってくる
	CObjBlock* objblock = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//ブロックとの当たり判定
	if(((UserData*)Save::GetData())->stagenum == 3)	//ステージ5
	{
		objblock->AllBlockHit(&m_px, &m_py, STAGE5_BOSS_BULLET_SIZE, STAGE5_BOSS_BULLET_SIZE,
			&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy);
	}
	else
	{
		objblock->BlockHit(&m_px, &m_py, BULLET_SIZE, BULLET_SIZE,
			&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy);
	}

	//ブロックとあたっていれば削除する
	if (m_hit_up == true || m_hit_down == true || m_hit_right == true || m_hit_left == true)
	{
		this->SetStatus(false);		//自身に消去命令を出す。
		Hits::DeleteHitBox(this);	//弾丸が所持するHitBoxを除去。
		return;
	}

	//弾丸のHitBox更新用ポインター取得
	CHitBox* hit = Hits::GetHitBox(this);

	//主人公とあたったら消去
	if (DeleteCheckObjNameHit(hit, this, OBJ_HERO))
	{
		return;
	}
	//岩とあたったら消去
	if (DeleteCheckObjNameHit(hit, this, OBJ_ROCK))
	{
		return;
	}
	//Water(水)とあたったら消去
	if (DeleteCheckObjNameHit(hit, this, OBJ_WATER))
	{
		return;
	}
	//Lastwall(壁)にあたったら消去
	if (DeleteCheckObjNameHit(hit, this, OBJ_LAST_WALL))
	{
		return;
	}
	//落ちるブロックにあたったら消去
	if (DeleteCheckObjNameHit(hit, this, OBJ_FALLING_BLOCK))
	{
		return;
	}

	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//ドロー
void CObjEnemyBullet::Draw()
{
	// マップ情報を持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };
	RECT_F src, dst;

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 32.0f;

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	
	if (((UserData*)Save::GetData())->stagenum == 2)//ステージ2なら
	{
		dst.m_right = dst.m_left + BULLET_SIZE;
		dst.m_bottom = dst.m_top + BULLET_SIZE;

		Draw::Draw(GRA_COCONUT, &src, &dst, color, m_r);
	}
	else
	{
		dst.m_right = dst.m_left + STAGE5_BOSS_BULLET_SIZE;
		dst.m_bottom = dst.m_top + STAGE5_BOSS_BULLET_SIZE;

		Draw::Draw(GRA_STAGE5_BOSS_BULLET, &src, &dst, color, m_r);
	}
}