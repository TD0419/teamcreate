#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"
#include "ObjBullet.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
//引数1	float x		:初期位置X
//引数2	float y		:初期位置Y
//引数3	float angle	:移動する角度
CObjBullet::CObjBullet(float x, float y,float r)
{
	//初期位置を決める
	m_px = x;
	m_py = y;

	// 角度(度数法)を入れる(回転方向が反対なので-にする)
	m_r = -r;

	// ラジアン角に変換
	r = r * 3.14f / 180.f; 

	// 角度から移動ベクトルを求める
	m_vx = cos(r);
	m_vy = sin(r);
}

//イニシャライズ
void CObjBullet::Init()
{
	m_speed = 8.0f; // 弾丸のスピード

	m_window_check = true;

	//ブロックとの当たり判定フラグの初期化
	m_hit_up	= false;
	m_hit_down	= false;
	m_hit_left	= false;
	m_hit_right = false;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, BULLET_SIZE, BULLET_SIZE, ELEMENT_PLAYER, OBJ_BULLET, 1);
}

//アクション
void CObjBullet::Action()
{	
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);
	//画面内か調べる
	m_window_check=WindowCheck(m_px,m_py,BULLET_SIZE,BULLET_SIZE);

	//画面外なら消去
	if(m_window_check==false)
	{
		this->SetStatus(false);		//自身に消去命令を出す。
		Hits::DeleteHitBox(this);	//弾丸が所持するHitBoxを除去。
		return;
	}
	
	//弾丸のHitBox更新用ポインター取得
	CHitBox* hit = Hits::GetHitBox(this);

	//敵とあたったら消去
	if (DeleteCheckObjNameHit(hit, this, OBJ_ENEMY))
	{
		return;
	}
	//BOSSと当たったら消去
	if (DeleteCheckObjNameHit(hit, this, OBJ_BOSS))
	{
		return;
	}
	//岩とあたったら消去
	if (DeleteCheckObjNameHit(hit, this, OBJ_ROCK))
	{
		return;
	}
	//Lastwall(壁)にあたったら消去
	if (DeleteCheckObjNameHit(hit, this, OBJ_LAST_WALL))
	{
		return;
	}
	//Water(水)とあたったら消去
	if (DeleteCheckObjNameHit(hit, this, OBJ_WATER))
	{
		return;
	}
	// リフト当たったら消去
	if (DeleteCheckObjNameHit(hit, this, OBJ_LIFT))
	{
		return;
	}
	//木と当たったら消去
	if (DeleteCheckObjNameHit(hit, this, OBJ_WOOD))
	{
		return;
	}
	//反射するブロックとあたった場合
	if (hit->CheckObjNameHit(OBJ_REFLECT_BLOCK) != nullptr)
	{
		HIT_DATA** hit_data;	//衝突の情報を入れる構造体
		hit_data = hit->SearchObjNameHit(OBJ_BLOCK);//衝突の情報をhit_dataに入れる

		for (int i = 0; i < hit->GetCount(); i++)
		{
			if (hit_data[i] != nullptr)
			{
				float r = hit_data[i]->r;

				//上　または　下で衝突している場合
				if (45.0f <= r && r < 135.0f || 225.0f <= r && r < 315.0f)
				{
					m_vy *= (-1.0f);//移動ベクトルの上下を反転する
				}
				else //左または右で衝突している場合
				{
					m_vx *= (-1.0f);//移動ベクトルの左右を反転する
				}
			}
		}
	}

	// ブロックオブジェクトを持ってくる
	CObjBlock* objblock = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	
	//ブロックとの当たり判定
	objblock->AllBlockHit(&m_px, &m_py, BULLET_SIZE, BULLET_SIZE,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy);

	//ブロックとあたっていれば削除する
	if (m_hit_up == true || m_hit_down == true || m_hit_right == true || m_hit_left == true)
	{
		this->SetStatus(false);		//自身に消去命令を出す。
		Hits::DeleteHitBox(this);	//弾丸が所持するHitBoxを除去。
		return;
	}
	
	//移動
	m_px += m_vx * m_speed;
	m_py += m_vy * m_speed;

	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);

}

//ドロー
void CObjBullet::Draw()
{
	//マップオブジェクトを持ってくる
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
	dst.m_top    = m_py - objmap->GetScrollY();
	dst.m_left   = m_px - objmap->GetScrollX();
	dst.m_right  = dst.m_left + BULLET_SIZE;
	dst.m_bottom = dst.m_top + BULLET_SIZE;

	Draw::Draw(GRA_HERO_BULLET, &src, &dst, color, m_r);
}