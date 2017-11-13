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
	m_px = x * BOSS_SIZE_WIDTH;
	m_py = y * BOSS_SIZE_HEIGHT;
}

//�C�j�V�����C�Y
void CObjStage5Boss::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;

	m_hp = 100; //��O�{�X�̂g�o(���ɂg�o��[100]�Ɛݒ�)

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