#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjCannon.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjCannon::CObjCannon(int x, int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
	m_map_x = x;
	m_map_y = y;
}

//イニシャライズ
void CObjCannon::Init()
{
	m_r = 0.0f;
	m_rec = 0;
		
	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, CANNON_SIZE_WIDTH, CANNON_SIZE_HEIGHT, ELEMENT_ENEMY, OBJ_CANNON, 1);
}

//アクション
void CObjCannon::Action()
{
	//画面外なら
	if (WindowCheck(m_px, m_py, CANNON_SIZE_WIDTH, CANNON_SIZE_HEIGHT) == false)
	{
		WindowOutDelete(this, m_map_x, m_map_y);//削除処理(復活あり)
		return;
	}

	m_rec++;//弾丸発射カウント開始

	if ( m_rec == 90 )
	{
		//debug弾丸作成
		CObjEnemyBullet* objenemy_bullet = new CObjEnemyBullet(m_px + 20.0f, m_py, 0);
		Objs::InsertObj(objenemy_bullet, OBJ_ENEMY_BULLET, 10);

		m_rec = 0;
		m_rec++;
	}

	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//ドロー
void CObjCannon::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top	 = 0.0f;
	src.m_left	 = 0.0f;
	src.m_right	 = 64.0f;
	src.m_bottom = 64.0f;

	//描画位置
	dst.m_top =  m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + CANNON_SIZE_WIDTH;
	dst.m_bottom = dst.m_top + CANNON_SIZE_HEIGHT;

	CObjHero* obj_hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	
	//主人公が生存している場合、角度の計算を行う
	if (obj_hero != nullptr)
	{
		float hero_x = obj_hero->GetPosX() - m_px;		//主人公の位置情報X取得
		float hero_y = obj_hero->GetPosY() - m_py;		//主人公の位置情報Y取得
		
		m_r = atan2(-hero_y, hero_x)*180.0f / 3.14f;
	
		if (m_r < 0.0f)
			m_r = 360.0f - abs(m_r);
	}

	//描画
	Draw::Draw(GRA_CANNON, &src, &dst, color, m_r);
}