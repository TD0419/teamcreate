#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjEnemy.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjEnemy::CObjEnemy(int x,int y)
{
	m_enemy_x = x * BLOCK_SIZE;
	m_enemy_y = y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjEnemy::Init()
{
	m_enemy_vx = 0.0f;
	m_enemy_vy = 0.0f;
}

//�A�N�V����
void CObjEnemy::Action()
{
}

//�h���[
void CObjEnemy::Draw()
{
}