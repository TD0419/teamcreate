#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjStage3Boss.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjStage3Boss::CObjStage3Boss(int x,int y)
{
	m_x = x * BOSS_SIZE;
	m_y = y * BOSS_SIZE;
}

//イニシャライズ
void CObjStage3Boss::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;

	m_hp = 20; //第三ボスのＨＰ(仮にＨＰを[ 20 ]と設定)
	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_x, m_y, BOSS_SIZE, BOSS_SIZE, ELEMENT_ENEMY, OBJ_BOSS, 1);

}

//アクション
void CObjStage3Boss::Action()
{
	//摩擦
	//m_vx += -(m_vx * 0.098);

	//自由落下運動
	//m_vy += 9.8 / (16.0f);
}

//ドロー
void CObjStage3Boss::Draw()
{

}