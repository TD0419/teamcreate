#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjBoss.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjBoss::CObjBoss(int x,int y)
{
	m_px = x * BOSS_SIZE;
	m_py = y * BOSS_SIZE;
}

//�C�j�V�����C�Y
void CObjBoss::Init()
{
   
    m_vx = 0.0f;
    m_vy = 0.0f;

	m_hp = 10; //�{�X�̂g�o(���ɂg�o��[ 10 ]�Ɛݒ�)

	 //�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, BOSS_SIZE, BOSS_SIZE, ELEMENT_ENEMY, OBJ_BOSS, 1);

}

//�A�N�V����
void CObjBoss::Action()
{
	
	//���C
	//m_vx += -(m_vx * 0.098);

	//���R�����^��
	//m_vy += 9.8 / (16.0f);

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);

}

//�h���[
void CObjBoss::Draw()
{

}