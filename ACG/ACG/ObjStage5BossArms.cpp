#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameL\Audio.h"
#include "GameHead.h"
#include "Function.h"

#include "ObjStage5BossArms.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjStage5BossArms::CObjStage5BossArms(int x, int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;

}

//�C�j�V�����C�Y
void CObjStage5BossArms::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;

	m_hp = 10; //��5�{�X�r�̂g�o(���ɂg�o��[10]�Ɛݒ�)

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_px + 160.0f, m_py + 138.0f, STAGE5_BOSS_ARMS_WIDTH_SIZE - 360.0f, STAGE5_BOSS_ARMS_HEIGHT_SIZE - 225.0f, ELEMENT_ENEMY, OBJ_STAGE5_BOSS_ARMS, 1);
	
}

//�A�N�V����
void CObjStage5BossArms::Action()
{

	//�����蔻��X�V
	HitBoxUpData(Hits::GetHitBox(this), m_px+160.0f, m_py + 138.0f);
	
}

//�h���[
void CObjStage5BossArms::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//���r---------------------------------------
	//�؂���ʒu
	src.m_top = STAGE5_BOSS_ARMS_HEIGHT_SIZE;
	src.m_left = 0.0f;
	src.m_right = src.m_left + STAGE5_BOSS_ARMS_WIDTH_SIZE;
	src.m_bottom = src.m_top + STAGE5_BOSS_ARMS_HEIGHT_SIZE;

	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY() ;
	dst.m_left = m_px - objmap->GetScrollX() ;
	dst.m_right = dst.m_left + STAGE5_BOSS_ARMS_WIDTH_SIZE;
	dst.m_bottom = dst.m_top + STAGE5_BOSS_ARMS_HEIGHT_SIZE;
	//�`��
	Draw::Draw(GRA_STAGE5_BOSS_ARMS_ALL, &src, &dst, color, 0.0f);

	//�E�r---------------------------------------
	//�؂���ʒu
	src.m_top = STAGE5_BOSS_ARMS_HEIGHT_SIZE;
	src.m_left = STAGE5_BOSS_ARMS_WIDTH_SIZE;
	src.m_right = src.m_left + STAGE5_BOSS_ARMS_WIDTH_SIZE;
	src.m_bottom = src.m_top + STAGE5_BOSS_ARMS_HEIGHT_SIZE;

	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = STAGE5_BOSS_ARMS_WIDTH_SIZE + m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + STAGE5_BOSS_ARMS_WIDTH_SIZE;
	dst.m_bottom = dst.m_top + STAGE5_BOSS_ARMS_HEIGHT_SIZE;
	//�`��
	Draw::Draw(GRA_STAGE5_BOSS_ARMS_ALL, &src, &dst, color, 0.0f);

}