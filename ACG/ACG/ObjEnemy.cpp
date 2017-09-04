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
	m_px = x * ENEMY_SIZE;
	m_py = y * ENEMY_SIZE;
}

//イニシャライズ
void CObjEnemy::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_r = 0.0f;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, ENEMY_SIZE,ENEMY_SIZE, ELEMENT_ENEMY, OBJ_ENEMY, 1);
}

//アクション
void CObjEnemy::Action()
{
	//移動----------------------------------------------

	//デバッグ用にボタン操作で動くようにしてます。
	//適当に移動処理をいじってもかまいません。

	//Aキーがおされたとき：左移動
	if (Input::GetVKey('J') == true)
	{
		m_vx -= 5.0f;
	}

	//Dキーがおされたとき：右移動
	if (Input::GetVKey('L') == true)
	{
		m_vx += 5.0f;
	}

	//摩擦
	//m_vx += -(m_vx * 0.098);

	//自由落下運動
	//m_vy += 9.8 / (16.0f);

	//移動ベクトルをポジションに加算
	m_px += m_vx;
	m_py += m_vy;

	//移動ベクトルを初期化
	m_vx = 0.0f;
	m_vy = 0.0f;

	//移動終わり-----------------------------------------

	//弾丸のHitBox更新用ポインター取得
	CHitBox* hit = Hits::GetHitBox(this);

	//弾丸とあたったら消去
	if (hit->SearchObjNameHit(OBJ_BULLET) != nullptr)
	{
		this->SetStatus(false);		//自身に消去命令を出す。
		Hits::DeleteHitBox(this);	//敵が所持するHitBoxを除去。
		//死んだのでマップ情報に自身の復活の儀式を行う。
		//儀式に必要なマップ情報を取得する
		CObjMap* map = (CObjMap*)Objs::GetObj(OBJ_MAP);
		//復活の儀式を行う
		map->SetMap(m_first_x, m_first_y, MAP_ENEMY);
		
		return;
	}

	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);

	
}

//ドロー
void CObjEnemy::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;

	//描画位置
	dst.m_top = 0.0f + m_py - obj_m->GetScrollY();
	dst.m_left = 0.0f + m_px - obj_m->GetScrollX();
	dst.m_right = dst.m_left + ENEMY_SIZE;
	dst.m_bottom = dst.m_top + ENEMY_SIZE;

	//描画
	Draw::Draw(1, &src, &dst, color, m_r);

}