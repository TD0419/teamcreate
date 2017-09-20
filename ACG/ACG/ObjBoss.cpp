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
	m_x = x * BOSS_SIZE;
	m_y = y * BOSS_SIZE;
}

//イニシャライズ
void CObjBoss::Init()
{
   
    m_vx = 300.0f;
    m_vy = 200.0f;
	m_r = 0.0f;
	m_hp = 10; //ボスのＨＰ(仮にＨＰを[ 10 ]と設定)

	 //当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_x, m_y, BOSS_SIZE , BOSS_SIZE , ELEMENT_ENEMY, OBJ_BOSS, 1);

}

//アクション
void CObjBoss::Action()
{
	//HitBox更新用ポインター取得
	CHitBox* hit = Hits::GetHitBox(this);

	//いずれもデバッグ用です。
	//Aキーがおされたとき：左移動
	if (Input::GetVKey('J') == true)
	{
		m_vx -= 0.5f;
	}

	//Dキーがおされたとき：右移動
	if (Input::GetVKey('L') == true)
	{
		m_vx += 0.5f;
	}

	//↑キーがおされたとき：上昇
	if (Input::GetVKey('I') == true)
	{
		m_vy = -10.0f;
	}
	//↓キーがおされたとき：下降
	//if (Input::GetVKey('M') == true)
	//{
	//	m_vy = 20.0f;
	//}
	//----------------------------------

	//摩擦
	m_vx += -(m_vx * 0.098);

	//自由落下運動
	m_vy += 9.8 / (16.0f);

	//移動ベクトルをポジションに加算
	m_x += m_vx;
	m_y += m_vy;


	//ブロックとの当たり判定実行
	CObjBlock* block = (CObjBlock*) Objs::GetObj(OBJ_BLOCK);
	block-> BlockHit(&m_x,&m_y,BOSS_SIZE,BOSS_SIZE,
	&m_hit_up,&m_hit_down,&m_hit_left,&m_hit_right,&m_vx,&m_vy
	);

	

	//弾丸とあたったらHP-1
	if (hit->SearchObjNameHit(OBJ_BULLET) != nullptr)
	{
		m_hp -= 1;
	}

	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_x, m_y);

}

//ドロー
void CObjBoss::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* map = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;

	//描画位置
	dst.m_top = 0.0f + m_y - map->GetScrollY();
	dst.m_left = 0.0f + m_x - map->GetScrollX();
	dst.m_right = dst.m_left  + BOSS_SIZE;
	dst.m_bottom = dst.m_top  + BOSS_SIZE;

	//描画
	Draw::Draw(14, &src, &dst, color, m_r);

}