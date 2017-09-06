#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"
#include "ObjEnemyBullet.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjEnemyBullet::CObjEnemyBullet(float x, float y, float angle)
{
	m_x = x;
	m_y = y;
	m_angle = angle;
	
}

//イニシャライズ
void CObjEnemyBullet::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_speed = 0.0f;

}

//アクション
void CObjEnemyBullet::Action()
{
	

}

//ドロー
void CObjEnemyBullet::Draw()
{
	

}