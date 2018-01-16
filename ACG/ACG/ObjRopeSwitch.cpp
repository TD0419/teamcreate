#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjRopeSwitch.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjRopeSwitch::CObjRopeSwitch(int x, int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
	m_map_x = x;
	m_map_y = y;
}

//�C�j�V�����C�Y
void CObjRopeSwitch::Init()
{
	m_rope_flag = false;
	//�����蔻��
	Hits::SetHitBox(this, m_px, m_py, 20, 20, ELEMENT_GIMMICK, OBJ_ROPE_SWITCH, 1);
}

//�A�N�V����
void CObjRopeSwitch::Action()
{
	//��ʊO�Ȃ�
	if (WindowCheck(m_px, m_py, 20.0f, 20.0f) == false)
	{
		WindowOutDelete(this, m_map_x, m_map_y);//�폜����(��������)
		return;
	}

	//���g��HitBox�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	//���t�g�I�u�W�F�N�g�������Ă���
	CObjLift* objlift = (CObjLift*)Objs::GetObj(OBJ_LIFT);

	if (objlift == nullptr)//���t�g�I�u�W�F�N�g���Ȃ����
	{
		switch (((UserData*)Save::GetData())->stagenum)
		{
		case 1://�X�e�[�W1
		{
			//���t�g�i�蓮�j�̐���
			CObjLift* objlift = new CObjLift(28, 22, 0, 640.0f,0);
			Objs::InsertObj(objlift, OBJ_LIFT, 9);
			break;
		}
		case 3://�X�e�[�W3	
		{
			//���t�g�i�蓮�j�̐���
			CObjLift* objlift = new CObjLift(29,22 ,0,640.0f ,0);
			Objs::InsertObj(objlift, OBJ_LIFT, 9);
			break;
		}
		}
	}

	//���[�v���������Ă����
	if (hit->CheckObjNameHit(OBJ_ROPE) != nullptr)
	{
		m_rope_flag = true;//�t���O��ON�ɂ���
	}
	else if(hit->CheckObjNameHit(OBJ_ROPE) == nullptr)
	{
		m_rope_flag = false;//�t���O��OFF�ɂ���
	}

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px+23.0f, m_py+32.0f);
}

//�h���[
void CObjRopeSwitch::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//�`��ʒu
	dst.m_top	 = m_py - objmap->GetScrollY();
	dst.m_left	 = m_px - objmap->GetScrollX();
	dst.m_right  = dst.m_left + ROPE_SWITCH_SIZE;
	dst.m_bottom = dst.m_top + ROPE_SWITCH_SIZE;

	//�`��
	Draw::Draw(GRA_ROPE_SWITCH, &src, &dst, color, 0);
}