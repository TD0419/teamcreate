//�g�p����w�b�_�[
#include "GameHead.h"
#include "ObjRollBlock.h"
#include "Function.h"

#include "GameL\HitBoxManager.h"

//�R���X�g���N�^
//����1,2	map�̗v�f�ԍ�
CObjRollBlock::CObjRollBlock(int x,int y,int pattan)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
	m_pattan = pattan;
}

//�C�j�V�����C�Y
void CObjRollBlock::Init()
{
	m_r = 0.0f;	//�p�x������
	m_count = 0;//�J�E���^�[�̏�����

	m_roll_flag = false;//��]�̃t���O��������
	
	switch (m_pattan)
	{
		case 1:	//90f���Ƃɉ�]
		{
			//��]�̒��S�ʒu�����߂�
			m_center_x = m_px + ROLL_BLOCK_SIZE_WIDTH / 2.0f;
			m_center_y = m_py + ROLL_BLOCK_SIZE_HEIGHT / 2.0f;

			//��]��̃|�W�V�����ƒ��S�ʒu�̍���
			m_difference_x = ROLL_BLOCK_SIZE_HEIGHT / 2.0f;
			m_difference_y = ROLL_BLOCK_SIZE_WIDTH / 2.0f;

			break;
		}
		case 2:	//�����������Ƃ��Ɉ�x�̂݉�]
		{
			break;
		}
	}

	//�����蔻��Z�b�g
	Hits::SetHitBox(this,m_px, m_py,ROLL_BLOCK_SIZE_WIDTH, ROLL_BLOCK_SIZE_HEIGHT, ELEMENT_BLOCK, OBJ_ROLL_BLOCK, 1);
}

//�A�N�V����
void CObjRollBlock::Action()
{
	if(m_count<=90)//90�ȉ��Ȃ�
		m_count++;//�J�E���g�𑝂₷

	switch (m_pattan)
	{
		case 1:	//90f���Ƃɉ�]
		{
			//90f�ɂȂ�����
			if (m_count == 90)
			{
				m_roll_flag = true;//��]�̃t���O���I���ɂ���
			}

			if (m_roll_flag == true)//��]�����Ƃ�
			{
				m_r += 90.0f;	//�p�x�����Z

				if (m_r >= 360.0f)	//360�x�ȏ�ɂȂ�Ȃ��悤�ɂ���
					m_r = 0.0f;

				//��]��̃|�W�V����������
				m_px = m_center_x - m_difference_x;
				m_py = m_center_y - m_difference_y;

				//�����̍X�V�ix��y�̓���ւ��j������
				float tmp = m_difference_x;
				m_difference_x = m_difference_y;
				m_difference_y = tmp;

				m_roll_flag = false;	//�t���O���I�t�ɂ���
				m_count = 0;			//�J�E���g��0�ŏ���������
			}
			break;
		}
		case 2:	//�����������Ƃ��Ɉ�x�̂݉�]
		{
			break;
		}
	}

	if( ((int)m_r % 180) ==0)	//�������Ȃ�
	{
		//�����ƕ������̂܂܂œ����蔻��̍X�V
		HitBoxUpData(Hits::GetHitBox(this), m_px, m_py, ROLL_BLOCK_SIZE_WIDTH, ROLL_BLOCK_SIZE_HEIGHT);
	}
	else 	//�c�����Ȃ�
	{
		//�����ƕ����t�ɂ��Ă����蔻��̍X�V
		HitBoxUpData(Hits::GetHitBox(this), m_px, m_py, ROLL_BLOCK_SIZE_HEIGHT, ROLL_BLOCK_SIZE_WIDTH);
	}
}

//�h���[
void CObjRollBlock::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = ROLL_BLOCK_SIZE_WIDTH;
	src.m_bottom = ROLL_BLOCK_SIZE_HEIGHT;

	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left =m_px - objmap->GetScrollX();

	if (((int)m_r % 180) == 0)	//������
	{
		dst.m_right = dst.m_left + ROLL_BLOCK_SIZE_WIDTH;
		dst.m_bottom = dst.m_top + ROLL_BLOCK_SIZE_HEIGHT;
	}
	else//�c����
	{
		dst.m_right = dst.m_left + ROLL_BLOCK_SIZE_HEIGHT;
		dst.m_bottom = dst.m_top + ROLL_BLOCK_SIZE_WIDTH;
	}

	//�`��
	Draw::Draw(GRA_ROLL_BLOCK, &src, &dst, color, m_r,-0.5f,-0.5f);
}
