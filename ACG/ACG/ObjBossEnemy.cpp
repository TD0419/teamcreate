#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjBossEnemy.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjBossEnemy::CObjBossEnemy()
{

}

//イニシャライズ
void CObjBossEnemy::Init()
{
    m_x  = 0.0f;
    m_y  = 0.0f;
    m_vx = 0.0f;
    m_vy = 0.0f;

	m_hp = 10; //ボスのＨＰ(仮にＨＰを[ 10 ]と設定)

}

//アクション
void CObjBossEnemy::Action()
{
	//摩擦
	//m_vx += -(m_vx * 0.098);

	//自由落下運動
	//m_vy += 9.8 / (16.0f);
}

//ドロー
void CObjBossEnemy::Draw()
{

}