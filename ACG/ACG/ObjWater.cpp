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
	m_py = y * WATER_SIZE_HEIGHT;
}

//�C�j�V�����C�Y
void CObjWater::Init()
{

	//�����蔻��
	Hits::SetHitBox(this, m_px, m_py, BLOCK_SIZE, WATER_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_WATER, 1);
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
			this->SetStatus(false);		//���g�ɍ폜���߂��o��
			Hits::DeleteHitBox(this);	//�₪���L����HitBox�ɍ폜����
			return;
		}

		m_water_gauge += 0.5f; // 1�����₵�Ă���

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

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 128.0f ;
	src.m_bottom = 64.0f;

	//�`��ʒu
	dst.m_top = m_py + m_water_gauge - obj_m->GetScrollY();
	dst.m_left = m_px - obj_m->GetScrollX();
	dst.m_right = dst.m_left + BLOCK_SIZE;
	dst.m_bottom = dst.m_top + WATER_SIZE_HEIGHT - m_water_gauge;
	//�`��
	Draw::Draw(11, &src, &dst, color, 0.0f);
}