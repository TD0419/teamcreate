//�g�p����w�b�_�[
#include "GameHead.h"
#include "GameL\WinInputs.h"
#include "ObjRollBlockSwitch.h"
#include "Function.h"

#include "GameL\HitBoxManager.h"

//�R���X�g���N�^
CObjRollBlockSwitch::CObjRollBlockSwitch(float x, float y, CObjRollBlock* p)
{
	//�ʒu��ݒ肷��
	m_px = x ;
	m_py = y ;

	//�u���b�N�̈ʒu�̕ۑ�
	m_base_block_px = x;
	m_base_block_py = y;

	//��Ղ̃|�C���^��ۑ�
	mp_base_block = p;
}

//�C�j�V�����C�Y
void CObjRollBlockSwitch::Init()
{
	m_pull_flag = false;
	m_lastroll = false;
	m_key_flag = false;
	m_r = 0.0f;
	m_once_flag = false;

	//�����蔻��
	Hits::SetHitBox(this, m_px, m_py, ROLL_BLOCK_SWITCH_SIZE_WIDTH, ROLL_BLOCK_SWITCH_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_ROLL_BLOCK_SWITCH, 1);
}

//�A�N�V����
void CObjRollBlockSwitch::Action()
{

	//��ʊO�Ȃ�
	if (WindowCheck(m_px, m_py, ROLL_BLOCK_SWITCH_SIZE_WIDTH, ROLL_BLOCK_SWITCH_SIZE_HEIGHT) == false)
	{
		CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//��������HitBox�������B

		return;
	}

	//HitBox�̃|�C���^�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	//map�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//����������I�t�ɂ���
	m_pull_flag = false;

	//���[�v�Ɠ������Ă����
	if (hit->CheckObjNameHit(OBJ_ROPE) != nullptr)
	{
		//���ړ����Ă����
		if (Input::GetVKey('A') == true)
		{
			m_once_flag = true; //��񂾂�
		}

		if(m_once_flag == true)
		{
			//92�x�𒴂��Ă����Ȃ�
			if (m_r >= 92.0f)
			{
				//����������I�t�ɂ���
				m_pull_flag = false;

				m_lastroll = true; 
				m_r = 92.0f;//90�𒴂��Ȃ��悤�ɂ���
			}
			else if (m_r < 92.0f) //92�x�ȉ��Ȃ�X�C�b�`����]������
			{
				m_r += 2.0f;//�p�x�̉��Z

				//��������̃t���O���I���ɂ���
				m_pull_flag = true;
				m_key_flag = true;
			}

			//sin�l�@cos�l�����߂�
			float sin = sinf(m_r * 3.14f / 180.0f);
			float cos = cosf(m_r * 3.14f / 180.0f);

			//�p�x�����Ɉʒu�𒲐߂���
			m_px = m_base_block_px - sin * ROLL_BLOCK_SIZE_WIDTH;
			m_py = m_base_block_py + ROLL_BLOCK_SIZE_WIDTH - cos * ROLL_BLOCK_SIZE_WIDTH;

		}

		//���[�v�I�u�W�F�N�g�������Ă���
		CObjRope* objrope = (CObjRope*)Objs::GetObj(OBJ_ROPE);

		//���[�v�̈ʒu�����̃I�u�W�F�N�g�̈ʒu�ɍ��킹��@+6.0f���邱�ƂŃ��[�v�ƃX�C�b�`����ɂ�����悤�ɂ���
		objrope->SetPosX(m_px + 6.0f);
		objrope->SetPosY(m_py + 6.0f);
	}

	//�t���O������
	mp_base_block->SetRollFlag(m_pull_flag);

	//hitBox�X�V
	HitBoxUpData(hit, m_px, m_py);
}

//�h���[
void CObjRollBlockSwitch::Draw()
{
	//map�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	float color[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src, dst;

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = ROLL_BLOCK_SWITCH_SIZE_WIDTH;
	src.m_bottom = ROLL_BLOCK_SWITCH_SIZE_HEIGHT;

	//�`��̈ʒu
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + ROLL_BLOCK_SWITCH_SIZE_WIDTH;
	dst.m_bottom = dst.m_top + ROLL_BLOCK_SWITCH_SIZE_HEIGHT;

	Draw::Draw(GRA_BLACK_BALL, &src, &dst, color, 0.0f);
}