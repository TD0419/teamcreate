#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjEnemy.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjEnemy::CObjEnemy()
{

}

//イニシャライズ
void CObjEnemy::Init()
{
	m_enemy_x  = 0.0f;
	m_enemy_y  = 0.0f;
	m_enemy_vx = 0.0f;
	m_enemy_vy = 0.0f;

}

//アクション
void CObjEnemy::Action()
{

}

//ドロー
void CObjEnemy::Draw()
{

}