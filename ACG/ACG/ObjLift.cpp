#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjLift.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjLift::CObjLift(int x, int y)
{
	m_px = x * LIFT_SIZE;
	m_py = y * LIFT_SIZE;
}

//�C�j�V�����C�Y
void CObjLift::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;

	//�����蔻��
	Hits::SetHitBox(this, m_px, m_py, LIFT_SIZE, LIFT_SIZE, ELEMENT_GIMMICK, OBJ_LIFT, 1);

}

//�A�N�V����
void CObjLift::Action()
{
	//���g��HitBox�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	//�ړ�
	m_px += m_vx;
	m_py += m_vy;

	//��l�����������Ă����
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		HeroRide();//��l�����悹�鏈��������
	}

	//���[�v�I�u�W�F�N�g�������Ă���
	CObjRopeSwitch* objrope_switch = (CObjRopeSwitch*)Objs::GetObj(OBJ_ROPE_SWITCH);
	
	if (objrope_switch->GetRopeFlag() == true)//���[�v�ƃ��[�v�X�C�b�`���������Ă���Ƃ�
	{
		m_vx = -1.0f;
	}
	else//���[�v�ƃ��[�v�X�C�b�`���������Ă��Ȃ��Ƃ�
	{
		m_vx = 1.0f;
	}

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//�h���[
void CObjLift::Draw()
{
	
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
				objhero->SetPosX(h_px + m_vx);//��l���̈ʒu�����Ƃ��Ǝ�l���������ʒu�{���t�g�̈ړ��ʂɂ���
				objhero->SetPosY(m_py - HERO_SIZE_HEIGHT);//��l���̃|�W�V���������t�g�̏�ɂ���
			}
		}
	}
}