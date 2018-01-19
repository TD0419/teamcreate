#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjDiffusionSource.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjDiffusionSource::CObjDiffusionSource(float x, float y, int limit)
{
	m_px = x;
	m_py = y;
	m_limit = limit;
}

//イニシャライズ
void CObjDiffusionSource::Init()
{
	m_vx = 0.0f;
	m_vy = 0.2f;

	//当たり判定セット
	Hits::SetHitBox(this, m_px, m_py, DIFFUSION_SOURCE_SIZE, DIFFUSION_SOURCE_SIZE, ELEMENT_ENEMY, OBJ_DIFFUSION_SOURCE, 1);
}

//アクション
void CObjDiffusionSource::Action()
{
	CHitBox* hit = Hits::GetHitBox(this);
	
	m_limit--;

	if (m_limit < 0)//リミットタイムが0以下なら
	{
		//5発同時発射
		CObjDiffusionBullet* p;
		for (int i = 210; i<360; i += 30)
		{
			//約30角度で角度弾丸発射
			p = new CObjDiffusionBullet(m_px + 28.0f, m_py + 20.0f, i,this);
			Objs::InsertObj(p, OBJ_DIFFUSION_BULLET, 100);
			Audio::Start(DIFFUSION);
		}
		
		this->SetStatus(false);		//自身を削除
		Hits::DeleteHitBox(this);	//ヒットボックスを削除
		return;
	}

	//落ちるブロックと当たったら消去
	if (DeleteCheckObjNameHit(hit, this, OBJ_FALLING_BLOCK))
	{
		return;
	}

	//移動
	m_px += m_vx;
	m_py += m_vy;

	//当たり判定の更新
	HitBoxUpData(hit, m_px, m_py);
}

//ドロー
void CObjDiffusionSource::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + DIFFUSION_SOURCE_SIZE;
	src.m_bottom = src.m_top + DIFFUSION_SOURCE_SIZE;

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + DIFFUSION_SOURCE_SIZE;
	dst.m_bottom = dst.m_top + DIFFUSION_SOURCE_SIZE;

	//描画
	Draw::Draw(GRA_DIFFUSION_SOURCE, &src, &dst, color, 0.0f);
}