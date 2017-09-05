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

	//移動----------------------------------------------

	//デバッグ用にボタン操作で動くようにしてます。
	//適当に移動処理をいじってもかまいません。

	//Aキーがおされたとき：左移動
	if (Input::GetVKey('J') == true)
	{
		m_posture = 0.0f;
		m_vx -= m_speed;
		m_ani_time ++;
	}

	//Dキーがおされたとき：右移動
	else if (Input::GetVKey('L') == true)
	{
		m_posture = 1.0f;
		m_vx += m_speed;
		m_ani_time ++;
	}
	else
	{
		m_ani_frame = 0; //キー入力が無い場合は静止フレームにする
		m_ani_time = 0;
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
		//儀式に必要なマップ情報を取得する
		CObjMap* map = (CObjMap*)Objs::GetObj(OBJ_MAP);
		//復活の儀式を行う
		map->SetMap(m_first_x, m_first_y, MAP_ENEMY);
		map->SetMapCreate(m_first_x, m_first_y, true);
		return;
	}
	
	//ブロックとのあたり判定
	obj_b->BlockHit(
		&m_x, &m_y, ENEMY_SIZE, ENEMY_SIZE, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, 
		&m_vx, &m_vy
	);

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