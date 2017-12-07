#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjNeedleStand.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjNeedleStand::CObjNeedleStand(int x, int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjNeedleStand::Init()
{
	//�����蔻��pHitBox���쐬                          
	Hits::SetHitBox(this, m_px, m_py, NEEDLE_STAND_SIZE, NEEDLE_STAND_SIZE, ELEMENT_GIMMICK, OBJ_NEEDLE_STAND, 1);

}

//�A�N�V����
void CObjNeedleStand::Action()
{
	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py - 32.0f);
}

//�h���[
void CObjNeedleStand::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�j�̓y��---------------------------------------------------

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + 640.0f;
	src.m_bottom = src.m_top + 64.0f;

	//�`��ʒu
	dst.m_top = m_py + 32.0f - objmap->GetScrollY() - NEEDLE_STAND_SIZE;
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + NEEDLE_STAND_SIZE;
	dst.m_bottom = dst.m_top + NEEDLE_STAND_SIZE;

	//�`��
	Draw::Draw(GRA_WIRE_MASH, &src, &dst, color, 0.0f);
	//-------------------------------------------------------
}