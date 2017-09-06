#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjEnemy.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjEnemy::CObjEnemy(int x, int y)
{
	//マップの要素数を補間
	m_first_x = x;
	m_first_y = y;
	m_x = x * ENEMY_SIZE;
	m_y = y * ENEMY_SIZE;
}

//イニシャライズ
void CObjEnemy::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_r = 0.0f;
	m_posture = 0.0f; //右向き1.0f 左向き0.0f

	m_ani_time = 0;
	m_ani_frame = 1;  //静止フレームを初期にする
	m_ani_max_time = 4; //アニメーション間隔幅

	m_speed = 0.5f;	//初期スピード

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_x, m_y, ENEMY_SIZE,ENEMY_SIZE, ELEMENT_ENEMY, OBJ_ENEMY, 1);
}

//アクション
void CObjEnemy::Action()
{
	//ブロック情報を持ってくる
	CObjBlock* obj_b = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//マップ情報を取ってくる
	CObjMap* map = (CObjMap*)Objs::GetObj(OBJ_MAP);
	//移動----------------------------------------------

	//左に向いているなら左へ移動する
	if (m_posture == 0.0)
	{
		m_vx -= m_speed;
		m_ani_time += 1;
	}
	//右に向いているなら右へ移動する
	else
	{
		m_vx += m_speed;
		m_ani_time += 1;
	}

	//アニメーションの感覚管理
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	//最後までアニメーションが進むと最初に戻る
	if (m_ani_frame == 2)
	{
		m_ani_frame = 0;
	}
	
	//摩擦
	m_vx += -(m_vx * 0.098);

	//自由落下運動
	m_vy += 9.8 / (16.0f);


	//移動ベクトルを初期化
	/*m_vx = 0.0f;
	m_vy = 0.0f;*/

	//移動終わり-----------------------------------------

	//弾丸のHitBox更新用ポインター取得
	CHitBox* hit = Hits::GetHitBox(this);

	//弾丸とあたったら消去
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{
		this->SetStatus(false);		//自身に消去命令を出す。
		Hits::DeleteHitBox(this);	//敵が所持するHitBoxを除去。
		//死んだのでマップ情報に自身の復活の儀式を行う。
		//復活の儀式を行う
		map->SetMap(m_first_x, m_first_y, MAP_ENEMY);
		map->SetMapCreate(m_first_x, m_first_y, true);
		return;
	}
	
	

	//ブロックとのあたり判定
	obj_b->BlockHit(
		&m_x, &m_y, ENEMY_SIZE, ENEMY_SIZE,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, 
		&m_vx, &m_vy
	);

	//右に衝突判定があったら左方向にする
	if (m_hit_left == true)
	{
		m_posture = 0.0;
	}
	//左に衝突判定があったら右方向にするです
	if (m_hit_right == true)
	{
		m_posture = 1.0;
	}

	//下に衝突判定がある
	if (m_hit_down == true)
	{
		//移動しようとしているところが崖なら方向転換
		//右に動いていて && 
		//右下にブロックが無かったら
		if (m_vx > 0 && map->GetMap((m_x / BLOCK_SIZE + 1), (m_y / BLOCK_SIZE + 1)) != MAP_BLOCK)
		{
			//方向を左にする
			m_posture = 0.0;
		}
		//左に移動していて &&
		//左下にブロックが無かったら		↓原点調整
		if (m_vx < 0 && map->GetMap(((m_x+ENEMY_SIZE) / BLOCK_SIZE - 1), (m_y / BLOCK_SIZE + 1)) != MAP_BLOCK)
		{
			//方向を右にする
			m_posture = 1.0;
		}
	}

	//移動ベクトルをポジションに加算
	m_x += m_vx;
	m_y += m_vy;

	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_x, m_y);

	
}

//ドロー
void CObjEnemy::Draw()
{
	//画像の切り取り配列
	int AniData[2] =
	{
		0  , 1 , 
	};

	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * 64;
	src.m_right = 64.0f + AniData[m_ani_frame] * 64;
	src.m_bottom = 64.0f;

	//描画位置
	dst.m_top = 0.0f + m_y - obj_m->GetScrollY();
	dst.m_left = (ENEMY_SIZE * m_posture) + m_x - obj_m->GetScrollX();
	dst.m_right = (ENEMY_SIZE - ENEMY_SIZE * m_posture) + m_x - obj_m->GetScrollX();
	dst.m_bottom = dst.m_top + ENEMY_SIZE;

	//描画
	Draw::Draw(8, &src, &dst, color, m_r);

}