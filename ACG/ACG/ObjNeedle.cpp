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
		m_py += NEEDLE_SIZE_HEIGHT;
	}
	
	//�����蔻��pHitBox���쐬                          
	Hits::SetHitBox(this, m_px, m_py, NEEDLE_SIZE_WIDTH, NEEDLE_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_NEEDLE, 1);
}

//�A�N�V����
void CObjNeedle::Action()
{
	//�{�X�I�u�W�F�N�g�̎擾
	CObjStage5Boss* objboss = (CObjStage5Boss*)Objs::GetObj(OBJ_STAGE5_BOSS);

	//�{�X������΃I�u�W�F�N�g�̍폜
	if (objboss != nullptr)
	{
		WindowOutDelete(this);
		return;
	}
	
	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�j���o������܂�
	if (m_needle_gauge < 32.0f)
	{
		m_needle_gauge += 0.5f;//�Q�[�W�𑝂₷
		
		//32.0�𒴂��Ȃ��悤�ɂ���
		if (m_needle_gauge > 32.0f)
			m_needle_gauge = 32.0f;
	}
	else //�j���o���؂��Ă���
	{
		m_time++;
		hit->SetInvincibility(true);//�j�̔�����Ȃ���
		
		if (m_time == 240) //240�t���[���o������j���o��
		{
			m_needle_gauge = 0.0f;
 			m_time = 0;
			hit->SetInvincibility(false);//�j�̔��������
		}
	}

	//�������̃g�Q���̓����蔻��
	if ( m_over_or_under == false )
	{
		HitBoxUpData(hit, m_px, m_py, NEEDLE_SIZE_WIDTH, NEEDLE_SIZE_HEIGHT - m_needle_gauge);
	}
	//������̃g�Q���̓����蔻��
	else
	{
		HitBoxUpData(hit, m_px, m_py + m_needle_gauge, NEEDLE_SIZE_WIDTH, NEEDLE_SIZE_HEIGHT- m_needle_gauge);
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
	
	//�؂���ʒu
	src.m_left = 0.0f;
	src.m_right = src.m_left + NEEDLE_SIZE_WIDTH;

	//�`��ʒu
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + NEEDLE_SIZE_WIDTH;


	//�������̃g�Q��`�悷��
	if (m_over_or_under == false)
	{
		//�؂���ʒu
		src.m_top = m_needle_gauge ;
		src.m_bottom = src.m_top + NEEDLE_SIZE_HEIGHT;

		//�`��ʒu
		dst.m_top = m_py - objmap->GetScrollY();
		dst.m_bottom = dst.m_top + NEEDLE_SIZE_HEIGHT - m_needle_gauge;
	}
	//������̃g�Q��`�悷��
	else 
	{
		//�؂���ʒu
		src.m_top = NEEDLE_SIZE_HEIGHT;
		src.m_bottom = m_needle_gauge;

		//�`��ʒu
		dst.m_top =  m_py - objmap->GetScrollY() + m_needle_gauge;
		dst.m_bottom = dst.m_top + NEEDLE_SIZE_HEIGHT -m_needle_gauge;
	}

	//�`��
	Draw::Draw(GRA_NEEDLE, &src, &dst, color, 0.0f);
}