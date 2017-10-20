#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjBoss.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjBoss::CObjBoss(int x,int y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//イニシャライズ
void CObjBoss::Init()
{
    m_vx = 0;
    m_vy = 0;
	m_r = 0.0f;
	m_hp = 20; //ボスのＨＰ
	m_ani_time = 0;
	m_ani_frame = 1;  //静止フレームを初期にする
	m_ani_max_time = 2; //アニメーション間隔幅
	
	 //当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, BOSS_SIZE , BOSS_SIZE , ELEMENT_ENEMY, OBJ_BOSS, 1);
}

//アクション
void CObjBoss::Action()
{
	m_ani_time++;//アニメーションは遊びなので消してもらってもおｋです
	//アニメーションの感覚管理
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	//最後までアニメーションが進むと最初にいく
	if (m_ani_frame == 8)
	{
		m_ani_frame = 0;
	}
	//HitBox更新用ポインター取得
	CHitBox* hit = Hits::GetHitBox(this);

	//摩擦
	m_vx += -(m_vx * 0.098f);

	//自由落下運動
	m_vy += 9.8f / (16.0f);

	//移動ベクトルをポジションに加算
	m_px += m_vx;
	m_py += m_vy;
	
	//ブロックとの当たり判定実行
	CObjBlock* objblock = (CObjBlock*) Objs::GetObj(OBJ_BLOCK);
	objblock-> BlockHit(&m_px,&m_py,BOSS_SIZE,BOSS_SIZE,
	&m_hit_up,&m_hit_down,&m_hit_left,&m_hit_right,&m_vx,&m_vy
	);
	
	CObjLastWall* objlastwall = (CObjLastWall*)Objs::GetObj(OBJ_LAST_WALL);
	//弾丸とあたったらHP-1
	if (hit->SearchObjNameHit(OBJ_BULLET) != nullptr)
	{
		m_hp -= 1;
	}

	if (m_hp == 0)
	{
		Hits::DeleteHitBox(this);	//bossが所有するHitBoxに削除する
		this->SetStatus(false);		//自身に削除命令を出す
		objlastwall->GateOpenflag = true;
		return;
	}

	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);

}

//ドロー
void CObjBoss::Draw()
{
	//画像の切り取り配列
	int AniData[8] =
	{
		0, 1, 2, 3, 4, 5, 6, 7,
	};
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = AniData[m_ani_frame] * 128.0-128.0;
	src.m_right = src.m_left-128.0f;
	src.m_bottom = src.m_top + 128.0f;;

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left  + BOSS_SIZE;
	dst.m_bottom = dst.m_top  + BOSS_SIZE+3;

	//描画
	Draw::Draw(4, &src, &dst, color, m_r);

}