#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjEnemy.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjEnemy::CObjEnemy(int x,int y)
{
	m_x = x;
	m_y = y;
}

//イニシャライズ
void CObjEnemy::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_x, m_y, 64.0f, 64.0f, ELEMENT_ENEMY, OBJ_ENEMY, 1);
}

//アクション
void CObjEnemy::Action()
{

	//摩擦
	//m_vx += -(m_vx * 0.098);

	//自由落下運動(重力)
	//m_vy += 9.8 / (16.0f);

	//弾丸のHitBox更新用ポインター取得
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_x, m_y);//HitBoxの位置を更新

	//弾丸とあたったら消去
	if (hit->SearchObjNameHit(OBJ_BULLET) != nullptr)
	{
		this->SetStatus(false);		//自身に消去命令を出す。
		Hits::DeleteHitBox(this);	//敵が所持するHitBoxを除去。
	}
}

//ドロー
void CObjEnemy::Draw()
{
}