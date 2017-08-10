#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjBullet.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjBullet::CObjBullet(float x,float y)
{

}

//イニシャライズ
void CObjBullet::Init()
{
    m_bullet_x = 0.0f;
    m_bullet_y = 0.0f;
    m_bullet_vx = 0.0f;
    m_bullet_vy = 0.0f;


}

//アクション
void CObjBullet::Action()
{

}

//ドロー
void CObjBullet::Draw()
{

}