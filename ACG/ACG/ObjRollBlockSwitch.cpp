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
	m_r = 0.0f;

	//�����蔻��
	Hits::SetHitBox(this, m_px, m_py, ROLL_BLOCK_SWITCH_SIZE_WIDTH, ROLL_BLOCK_SWITCH_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_ROLL_BLOCK_SWITCH, 1);
}

//�A�N�V����
void CObjRollBlockSwitch::Action()
{
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
			m_r += 2.0f;//�p�x�̉��Z

			//sin�l�@cos�l�����߂�
			float m_sin = sinf(m_r * 3.14f / 180.0f);
			float m_cos = cosf(m_r * 3.14f / 180.0f);

			//�p�x�����Ɉʒu�𒲐߂���
			m_px = m_base_block_px - m_sin * ROLL_BLOCK_SIZE_WIDTH;
			m_py = m_base_block_py + ROLL_BLOCK_SIZE_WIDTH - m_cos * ROLL_BLOCK_SIZE_WIDTH;
			
			//��������̃t���O���I���ɂ���
			m_pull_flag=true;
		}
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

	Draw::Draw(GRA_ROLL_BLOCK_SWITCH, &src, &dst, color, 0.0f);
}