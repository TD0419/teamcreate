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
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjStage5Boss::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;

	m_hp = 100; //��5�{�X�̂g�o(���ɂg�o��[100]�Ɛݒ�)

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, STAGE5_BOSS_BODY_SIZE, STAGE5_BOSS_BODY_SIZE, ELEMENT_ENEMY, OBJ_STAGE5_BOSS, 1);
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
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + STAGE5_BOSS_BODY_SIZE;
	src.m_bottom = src.m_top + STAGE5_BOSS_BODY_SIZE;
	
	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = STAGE5_BOSS_BODY_SIZE + m_px - objmap->GetScrollX();
	dst.m_bottom = dst.m_top + STAGE5_BOSS_BODY_SIZE;

	//�`��
	Draw::Draw(GRA_STAGE5_BOSS_BODY, &src, &dst, color, 0.0f);
}