#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"
#include "ObjEnemyBullet.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjEnemyBullet::CObjEnemyBullet(float x, float y, float angle)
{
	m_x = x;
	m_y = y;
	m_angle = angle;
	
}

//�C�j�V�����C�Y
void CObjEnemyBullet::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_speed = 0.0f;

}

//�A�N�V����
void CObjEnemyBullet::Action()
{
	

}

//�h���[
void CObjEnemyBullet::Draw()
{
	

}