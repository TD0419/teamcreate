#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"
#include "ObjLift.h"
#include "Function.h"
#include <math.h>

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^(�ړ��̃x�N�g�����j
//����1,2	�}�b�v�̐��l(�ʒu)
//����3,4	�ړ�����Ƃ��̑��x
//����5		�ړ��̍ő�ʁi���E�j
//����6		�ړ��̍ő�ʁi�㉺�j
//����		�ړ��̂��߂̃t���O�̔z��̗v�f��	����ɉ�������̂ł��̂܂܂����Ƃ��Ă�������
CObjLift::CObjLift(int px, int py,float vx,float vy,float width_max, float length_max)
{
	//�\�����ׂ��ʒu������
	m_px = (float)px * BLOCK_SIZE;	
	m_py = (float)py * BLOCK_SIZE;
	
	//�ړ��x�N�g��������
	m_vx = vx;
	m_vy = vy;

	//�ړ��̍ő�ʂ�����
	m_width_max = width_max;	
	m_length_max = length_max;
}

//�R���X�g���N�^
CObjLift::CObjLift(int px,int py)
{
	m_px = (float)px * BLOCK_SIZE;
	m_py = (float)py * BLOCK_SIZE;
	m_vx = 0.0f;
	m_vy = 0.0f;

}

//�C�j�V�����C�Y
void CObjLift::Init()
{
	m_move_x = 0.0f;
	m_move_y = 0.0f;

	//�����蔻��
	Hits::SetHitBox(this, m_px, m_py, LIFT_SIZE_WIDTH, LIFT_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_LIFT, 1);

}

//�A�N�V����
void CObjLift::Action()
{
	//���g��HitBox�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	//��l�����������Ă����
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		HeroRide();//��l�����悹�鏈��������
	}

	//���[�v�I�u�W�F�N�g�������Ă���
	CObjRopeSwitch* objrope_switch = (CObjRopeSwitch*)Objs::GetObj(OBJ_ROPE_SWITCH);
	
	//��p�I�߂��ăp�^�[���킯���K�v�Ȃ̂łƂ肠�����R�����g�����Ă��܂�
	//if (objrope_switch->GetRopeFlag() == true)//���[�v�ƃ��[�v�X�C�b�`���������Ă���Ƃ�
	//{
	//	if (Input::GetVKey('A'))
	//		m_vx = -1.0f;
	//	else
	//		m_vx = 0.0f;
	//}
	//else//���[�v�ƃ��[�v�X�C�b�`���������Ă��Ȃ��Ƃ�
	//{
	//	m_vx = 1.0f;
	//}

	//���E�̈ړ��ʒ���
	if (m_move_x > m_width_max)	//�ړ��ʂ��ő�ʂ𒴂����
	{
		m_vx *= (-1);	//�ړ������𔽓]����
		m_move_x = 0.0f;//�ړ��ʂ̏�����
	}

	//�㉺�̈ړ��ʒ���
	if (m_move_y > m_length_max)	//�ړ��ʂ��ő�ʂ𒴂����
	{
		m_vy *= (-1);	//�ړ������𔽓]����
		m_move_y = 0.0f;//�ړ��ʂ̏�����
	}	

	//�ړ�
	m_px += m_vx;
	m_py += m_vy;

	//�ړ��ʂ̕ۑ�
	m_move_x += abs(m_vx);
	m_move_y += abs(m_vy);

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(hit, m_px, m_py);
}

//�h���[
void CObjLift::Draw()
{	
	//map�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�`��F�����߂�
	float color[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src, dst;

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 128.0f;
	src.m_bottom = 128.0f;

	//�`��̈ʒu
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + LIFT_SIZE_WIDTH;
	dst.m_bottom = dst.m_top + LIFT_SIZE_HEIGHT;

	//���t�g�̕`��
	Draw::Draw(GRA_LIFT, &src, &dst, color, 0.0f);
}

//��l�����悹�鏈��������
void CObjLift::HeroRide()
{
	//���g��HitBox�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	HIT_DATA** hit_data;	//�Փ˂̏�������\����
	hit_data = hit->SearchObjNameHit(OBJ_HERO);//�Փ˂̏���hit_data�ɓ����

	for (int i = 0; i < hit->GetCount(); i++)
	{
		if (hit_data[i] != nullptr)
		{
			float r = hit_data[i]->r;//�������Ă���p�x�������Ă���

			//�㑤���������Ă���΂�
			if (45.0f <= r && r <= 135.0f)
			{
				//��l���I�u�W�F�N�g�������Ă���
				CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);
				float h_px = objhero->GetPosX();//��l���̈ʒuX�������Ă���

				objhero->SetHitDown(true);//���t�g�̏�Ɏ�l��������Ă�����m_hit_down��true��Ԃ�

				//���t�g�ɏ悹�鏈��
				objhero->SetVecY(0.0f);//��l����Y�����̈ړ���0�ɂ���
				objhero->SetPosX(h_px + m_vx);//��l���̈ʒu�����Ƃ��Ǝ�l���������ʒu�{���t�g�̈ړ��ʂɂ���
				objhero->SetPosY(m_py - HERO_SIZE_HEIGHT+1.0f);//��l���̃|�W�V���������t�g�̏�ɂ���
			}
		}
	}
}