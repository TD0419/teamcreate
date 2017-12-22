#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjNeedle.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjNeedle::CObjNeedle(int x, int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
	m_map_x = x;
	m_map_y = y;
}

//�C�j�V�����C�Y
void CObjNeedle::Init()
{
	m_needle_gauge = 0.0f;
	m_time = 0;
	m_over_or_under = false;//true�c�g�Q�̑�̏�ɂ���@false�c��̉��ɂ���

	//�}�b�v�̃I�u�W�F�N�g�����擾
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�g�Q�̑�̃I�u�W�F�N�g�����擾
	CObjNeedleStand* obj_needle_stand = (CObjNeedleStand*)Objs::GetObj(OBJ_NEEDLE_STAND);

	//�}�b�v��(csv�f�[�^)�Ńg�Q�̔ԍ��̉��ɑ�̔ԍ������邩�𒲂ׂ�
	int stand_block_num = objmap->GetMap((int)m_px / ((int)BLOCK_SIZE), ((int)m_py / ((int)BLOCK_SIZE)) + 1);

	//���Ƀg�Q�̑�(�ԍ�)������΁A������̃g�Q��\��������
	if ( stand_block_num == MAP_NEEDLE_STAND)
	{
		//�g�Q�̑�̏�ɂ���Ɣ��ʂ���
		m_over_or_under = true;//������̃g�Q��\�����邽�߂̏���

	}
	
	//�����蔻��pHitBox���쐬                          
	Hits::SetHitBox(this, m_px, m_py, NEEDLE_SIZE_WIDTH, NEEDLE_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_NEEDLE, 1);

}

//�A�N�V����
void CObjNeedle::Action()
{
	////��ʊO�Ȃ�
	//if (WindowCheck(m_px, m_py, NEEDLE_SIZE_WIDTH, NEEDLE_SIZE_HEIGHT) == false)
	//{
	//	WindowOutDelete(this, m_map_x, m_map_y);//�폜����(��������)
	//	return;
	//}

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�j���Ō�܂ŏo�Ă��Ȃ���
	if (m_needle_gauge != 64)
		m_needle_gauge++;

	else //�j���Ō�܂ŏo���ꍇ
	{
		m_time++;
		hit->SetInvincibility(true);//�j�̔�����Ȃ���
		if (m_time == 240) //120�t���[���o������j���o��
		{
			m_needle_gauge = 0;
 			m_time = 0;
			hit->SetInvincibility(false);//�j�̔��������
		}
		
	}
	//�������̃g�Q���̓����蔻�茸������
	if (m_over_or_under == false)
	{
		// hitbox���������Ȃ�
		hit->SetPos(m_px - objmap->GetScrollX(), m_py - objmap->GetScrollY(), NEEDLE_SIZE_WIDTH, NEEDLE_SIZE_HEIGHT - m_needle_gauge / 2);

	}
	//������̃g�Q���̓����蔻�茸������
	else if (m_over_or_under == true)
	{
		hit->SetPos(m_px - objmap->GetScrollX(), m_py + NEEDLE_SIZE_HEIGHT - objmap->GetScrollY() + m_needle_gauge / 2, NEEDLE_SIZE_WIDTH, NEEDLE_SIZE_HEIGHT - m_needle_gauge / 2);

	}
}

//�h���[
void CObjNeedle::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);
	
	//�������̃g�Q��`�悷��
	if (m_over_or_under == false)
	{
		//�؂���ʒu
		src.m_top = 0.0f + m_needle_gauge / 2;
		src.m_left = 0.0f;
		src.m_right = src.m_left + NEEDLE_SIZE_WIDTH;
		src.m_bottom = src.m_top + NEEDLE_SIZE_HEIGHT;

		//�`��ʒu
		dst.m_top = m_py - objmap->GetScrollY();
		dst.m_left = m_px - objmap->GetScrollX();
		dst.m_right = dst.m_left + NEEDLE_SIZE_WIDTH;
		dst.m_bottom = dst.m_top + NEEDLE_SIZE_HEIGHT - m_needle_gauge / 2;
	}
	//������̃g�Q��`�悷��
	else if (m_over_or_under == true)
	{
		//�؂���ʒu
		src.m_top = NEEDLE_SIZE_HEIGHT;
		src.m_left = 0.0f;
		src.m_right = src.m_left + NEEDLE_SIZE_WIDTH;
		src.m_bottom = 0.0f + m_needle_gauge / 2;

		//�`��ʒu
		dst.m_top = NEEDLE_SIZE_HEIGHT + m_py - objmap->GetScrollY() + m_needle_gauge / 2;
		dst.m_left = m_px - objmap->GetScrollX();
		dst.m_right = dst.m_left + NEEDLE_SIZE_WIDTH;
		dst.m_bottom = (NEEDLE_SIZE_HEIGHT + NEEDLE_SIZE_HEIGHT) + m_py - objmap->GetScrollY();
	}

	//�`��
	Draw::Draw(GRA_NEEDLE, &src, &dst, color, 0.0f);
}