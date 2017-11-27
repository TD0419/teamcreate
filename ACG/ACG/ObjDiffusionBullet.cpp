#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjDiffusionBullet.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjDiffusionBullet::CObjDiffusionBullet(float x, float y, int r)
{
	m_px = x ;
	m_py = y ;
	m_r  = (float)r;
}

//イニシャライズ
void CObjDiffusionBullet::Init()
{
	
	m_vx = cos(3.14f / 180.0f*m_r);
	m_vy = sin(3.14f / 180.0f*m_r);
	m_speed = 5.5f;
	m_window_check = true;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 12.0f, 12.0f, ELEMETN_ITEM, OBJ_DIFFUSION_BULLET, 1);
}

//アクション
void CObjDiffusionBullet::Action()
{
	//移動
	m_px += m_vx* m_speed;
	m_py -= m_vy* m_speed;

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
	if (hit->CheckElementHit(OBJ_HERO) == true)
	{
		this->SetStatus(false);		//自身に消去命令を出す。
		Hits::DeleteHitBox(this);	//弾丸が所持するHitBoxを除去。
		return;
	}

	//lastwallと当たったら消去
	if (hit->CheckObjNameHit(OBJ_LAST_WALL) != nullptr)
	{
		this->SetStatus(false);		//自身に消去命令を出す。
		Hits::DeleteHitBox(this);	//弾丸が所持するHitBoxを除去。
		return;
	}

	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px + 30.0f, m_py);
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
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + 12.0f;
	dst.m_bottom = dst.m_top + 12.0f;

	Draw::Draw(GRA_CANNON_BEAM, &src, &dst, color, m_r);

}