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
	m_r = 0.0f;
	m_rotation_flag = false;//��]�͂܂����Ȃ�

	m_rope_hit_flag = false;//�����͏Փ˂��Ă�����

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


	//��]�t���O��ON�Ȃ�
	if (m_rotation_flag == true)
	{
		
		//90�x�ȉ��Ȃ�X�C�b�`����]������
		if (m_r < 90.0f) 
		{
			//���[�v�Ɖ�]�u���b�N�X�C�b�`�̈ʒu�𒲐�����
			PositionAdjustment();
			m_r += 2.0f;//�p�x�̉��Z
		}
	}
	//90�x�ȏォ���[�v�ƐڐG���Ă�����
	//���[�v�������A90�x�ɂ���
	if (m_r >= 90.0f && hit->CheckObjNameHit(OBJ_ROPE) != nullptr)
	{
		//��]���I�����Ă���̂Ń��[�v����������
		CObjRope* objrope = (CObjRope*)Objs::GetObj(OBJ_ROPE);
		if (objrope != nullptr)
			objrope->Delete();

		m_r = 90.0f;//90�𒴂��Ȃ��悤�ɂ���
	}

	//���[�v�Ɠ������Ă���
	if (hit->CheckObjNameHit(OBJ_ROPE) != nullptr)
	{
		//1�t���[���O�A�t���O��OFF�Ȃ烍�[�v�̈ʒu�𒲐�����
		if (m_rope_hit_flag == false)
		{
			//���[�v�Ɖ�]�u���b�N�X�C�b�`�̈ʒu�𒲐�����
			//���ł����Ă����Ȃ��Ɖ�]�u���b�N�X�C�b�`�̏�̂ق��Ń��[�v����������������
			//��u����Hit����͋N���邪����ȍ~Hit���薳����ԂɂȂ��Ă��܂��̂�
			//�����ňʒu�𒲐�����
			PositionAdjustment();
			//�Փ˂��Ă���̂Ńt���O��ON�ɂ���
			m_rope_hit_flag = true;
		}
		//A�L�[�����͂��ꂽ��
		//��]�t���O��ON(��]����)�ɂ���
		if (Input::GetVKey('A') == true)
		{
			m_rotation_flag = true; //��]������
			//�t���O������
			mp_base_block->SetRollFlag(m_rotation_flag);
		}
	}
	else
		m_rope_hit_flag = false;
	
	//hitBox�X�V
	HitBoxUpData(hit, m_px, m_py);

	//��]���Ō�܂ł����Ă����玩�g����������
	//��]���I��������s�K�v�Ǝv�����̂ŏ������܂����B
	if (m_r >= 90.0f)
		WindowOutDelete(this);
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

	Draw::Draw(GRA_TARZAN_POINT, &src, &dst, color, 0.0f);
}

//���[�v�Ɖ�]�u���b�N�X�C�b�`�̈ʒu�𒲐�����֐�
void CObjRollBlockSwitch::PositionAdjustment()
{
	//sin�l�@cos�l�����߂�
	float sin = sinf(m_r * 3.14f / 180.0f);
	float cos = cosf(m_r * 3.14f / 180.0f);

	//�p�x�����Ɉʒu�𒲐߂���
	m_px = m_base_block_px - sin * ROLL_BLOCK_SIZE_WIDTH;
	m_py = m_base_block_py + ROLL_BLOCK_SIZE_WIDTH - cos * ROLL_BLOCK_SIZE_WIDTH;

	//���[�v�I�u�W�F�N�g�������Ă���
	CObjRope* objrope = (CObjRope*)Objs::GetObj(OBJ_ROPE);
	if (objrope != nullptr)
	{
		//���[�v�̈ʒu�����̃I�u�W�F�N�g�̈ʒu�ɍ��킹��@+6.0f���邱�ƂŃ��[�v�ƃX�C�b�`����ɂ�����悤�ɂ���
		objrope->SetPosX(m_px + 6.0f);
		objrope->SetPosY(m_py + 6.0f);
	}
}