#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "Function.h"
#include "ObjStage5Boss.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjStage5Boss::CObjStage5Boss(int x, int y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjStage5Boss::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;

	m_hp = 100; //��5�{�X�̂g�o(���ɂg�o��[100]�Ɛݒ�)

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, BOSS_SIZE_WIDTH, BOSS_SIZE_HEIGHT, ELEMENT_ENEMY, OBJ_STAGE5_BOSS, 1);
}

//�A�N�V����
void CObjStage5Boss::Action()
{

	//�����蔻��X�V
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//�h���[
void CObjStage5Boss::Draw()
{

}