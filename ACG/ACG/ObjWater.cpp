//�g�p����w�b�_�[�t�@�C���@
#include "GameL\HitBoxManager.h"
#include "GameL\WinInputs.h"
#include "GameHead.h"
#include "ObjWater.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjWater::CObjWater(int x, int y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjWater::Init()
{

	//�����蔻��
	Hits::SetHitBox(this, m_px, m_py, BLOCK_SIZE, BLOCK_SIZE, ELEMENT_PLAYER, OBJ_WATER, 1);
	m_water_gauge = 0.0f;
}

//�A�N�V����
void CObjWater::Action()
{	
	CHitBox* hitbox = Hits::GetHitBox(this);
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	// m_water_gauge��64���z�����珈���X�g�b�v
	if (m_water_gauge >= 64)
	{
		return;
	}

	m_water_gauge+=1; // 1�����₵�Ă���

	// hitbox���������Ȃ�
	hitbox->SetPos(m_px - obj_m->GetScrollX(), m_py - obj_m->GetScrollY() + m_water_gauge, BLOCK_SIZE - m_water_gauge, BLOCK_SIZE);

}

//�h���[
void CObjWater::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�`��ʒu
	dst.m_top    = m_py - obj_m->GetScrollY() + m_water_gauge;
	dst.m_left   = m_px - obj_m->GetScrollX();
	dst.m_right  = dst.m_left + BLOCK_SIZE; 
	dst.m_bottom = 512.0f - obj_m->GetScrollY() + BLOCK_SIZE; // bottom�͍��W���Œ肷��

	//�`��
	Draw::Draw(8, &src, &dst, color, 0.0f);
}