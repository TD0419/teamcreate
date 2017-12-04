#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjEnemyBullet.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
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

	//主人公との角度の計算を行う-----------------------------
	//主人公のオブジェクト情報を持ってくる
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hero_x = objhero->GetPosX() - objmap->GetScrollX();		//主人公の位置情報X取得
	float hero_y = objhero->GetPosY() - objmap->GetScrollY();		//主人公の位置情報Y取得

	//主人公の位置ベクトル情報取得
	float Hvector_x = hero_x - x ;
	float Hvector_y = hero_y - y ;

	//斜辺取得
	float hypotenuse = sqrt(Hvector_y * Hvector_y + Hvector_x * Hvector_x);

	//角度を求める
	m_r = acos(Hvector_x / hypotenuse);

	//----------------------------------------------------------

	//角度方向に弾丸を移動させる
	m_vx = cos(m_r) * m_speed;
	m_r = m_r * 180.0f / 3.14f;

	//マウスのY位置が主人公のY位置より下だったら
	if (hero_y > y)
	{
		//180°～360°の値にする
		m_r = 360 - abs(m_r);
	}
	//マウスのY位置が初期Y位置より上
	if (hero_y < y)
	{
		m_vy = -sin(acos(Hvector_x / hypotenuse)) * m_speed;
	}
	else
	{
		m_vy = sin(acos(Hvector_x / hypotenuse)) * m_speed;
	}
	
}

//イニシャライズ
void CObjEnemyBullet::Init()
{
	/*
	m_vx = 0.0f;
	m_vy = 1.0f;
	m_speed = 0.0f;
	
	m_vx = cos(m_angle) * m_speed;
	m_angle = m_angle * 180.0 / 3.14;
	*/

	m_window_check = true;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, BULLET_SIZE, BULLET_SIZE, ELEMENT_ENEMY, OBJ_ENEMY_BULLET, 1);
}

//アクション
void CObjEnemyBullet::Action()
{
	//移動
	m_px += m_vx*1.0f;
	m_py += m_vy*1.0f;

	//画面内か調べる
	m_window_check = WindowCheck(m_px, m_py, BULLET_SIZE, BULLET_SIZE);

	//画面外なら消去
	if (m_window_check == false)
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
	dst.m_right = dst.m_left + BULLET_SIZE;
	dst.m_bottom = dst.m_top + BULLET_SIZE;

	Draw::Draw(GRA_COCONUT, &src, &dst, color, m_r);

}