#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjTarzanPoint.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjTarzanPoint::CObjTarzanPoint(int x, int y,bool look_flag)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
	m_map_x = x;
	m_map_y = y;

	m_look_flag = look_flag;
}

//�C�j�V�����C�Y
void CObjTarzanPoint::Init()
{
	//�����蔻��
	Hits::SetHitBox(this, m_px, m_py, TARZAN_POINT_WIDTH, TARZAN_POINT_HEIGHT, ELEMENT_GIMMICK, OBJ_TARZAN_POINT, 1);
}

//�A�N�V����
void CObjTarzanPoint::Action()
{
	//�{�X�I�u�W�F�N�g�������Ă���
	CObjStage5Boss* objboss = (CObjStage5Boss*)Objs::GetObj(OBJ_STAGE5_BOSS);
	
	//���[�v�I�u�W�F�N�g�������Ă���
	CObjRope* objrope = (CObjRope*)Objs::GetObj(OBJ_ROPE);

	//HitBox�̃|�C���^�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	//�X�e�[�W5�{�X�I�u�W�F�N�g�������
	if (objboss != nullptr)
	{
		//�X�e�[�W5�{�X��|������A�I�u�W�F�N�g���폜����
		if (objboss->GetBossDeathFlag() == true)
		{
			this->SetStatus(false);		//���g�ɏ������߂��o���B
			Hits::DeleteHitBox(this);	//�G����������HitBox�������B
			return;

		}
		//4�Ԗڂ̍U���Ȃ�
		if (objboss->GetAttackMode() == 4)
			m_look_flag = true;
		else
			m_look_flag = false;
	}

	if (m_look_flag == false)//�����Ȃ���ԂȂ�
	{
		Hits::DeleteHitBox(this);	//��������HitBox�������B
		return;
	}
	

	//���[�v�Ɠ������Ă���Ȃ烍�[�v�̈ʒu�����킹��
	if (hit != nullptr)
	{
	
		if (hit->CheckObjNameHit(OBJ_ROPE) != nullptr)
		{
			//���[�v�̈ʒu�����̃I�u�W�F�N�g�̈ʒu�ɍ��킹��@+2.0f���邱�ƂŃ��[�v�ƃX�C�b�`����ɂ�����悤�ɂ���
			objrope->SetPosX(m_px + 6.0f);
			objrope->SetPosY(m_py + 6.0f);
		}
	}
	//��ʊO�Ȃ�
	if (WindowCheck(m_px, m_py, TARZAN_POINT_WIDTH, TARZAN_POINT_HEIGHT) == false )
	{
		WindowOutDelete(this, m_map_x, m_map_y);//�폜����(��������)
		return;
	}

	//�����蔻�肪�Ȃ���Γ����蔻����Z�b�g
	if (hit == nullptr)
	{
		Hits::SetHitBox(this, m_px, m_py, TARZAN_POINT_WIDTH, TARZAN_POINT_HEIGHT, ELEMENT_GIMMICK, OBJ_TARZAN_POINT, 1);
	}

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//�h���[
void CObjTarzanPoint::Draw()
{
	if (m_look_flag == false)	//�����Ȃ���ԂȂ�
		return;

	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = TARZAN_POINT_WIDTH;
	src.m_bottom = TARZAN_POINT_HEIGHT;

	//�`��ʒu
	dst.m_top    = m_py - objmap->GetScrollY();
	dst.m_left   = m_px - objmap->GetScrollX();
	dst.m_right  = dst.m_left + TARZAN_POINT_WIDTH;
	dst.m_bottom = dst.m_top + TARZAN_POINT_HEIGHT;

	//�`��
	Draw::Draw(GRA_TARZAN_POINT, &src, &dst, color, 0.0f);

}