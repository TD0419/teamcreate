#include "GameL\DrawTexture.h"
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
	m_px = x * BOSS_SIZE;
	m_py = y * BOSS_SIZE;
}

//イニシャライズ
void CObjBoss::Init()
{
   
    m_vx = 0.0f;
    m_vy = 0.0f;

	m_hp = 10; //ボスのＨＰ(仮にＨＰを[ 10 ]と設定)

	 //当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, BOSS_SIZE, BOSS_SIZE, ELEMENT_ENEMY, OBJ_BOSS, 1);

}

//アクション
void CObjBoss::Action()
{
	
	//摩擦
	//m_vx += -(m_vx * 0.098);

	//自由落下運動
	//m_vy += 9.8 / (16.0f);

	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);

}

//ドロー
void CObjBoss::Draw()
{

}