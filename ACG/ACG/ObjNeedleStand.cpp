#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjNeedleStand.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjNeedleStand::CObjNeedleStand(int x, int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
	m_map_x = x;
	m_map_y = y;
}

//�C�j�V�����C�Y
void CObjNeedleStand::Init()
{
	//�����蔻��pHitBox���쐬                          
	Hits::SetHitBox(this, m_px, m_py, NEEDLE_STAND_SIZE, NEEDLE_STAND_SIZE, ELEMENT_GIMMICK, OBJ_NEEDLE_STAND, 1);

}

//�A�N�V����
void CObjNeedleStand::Action()
{

	//��ʊO�Ȃ�
	if (WindowCheck(m_px, m_py, NEEDLE_STAND_SIZE, NEEDLE_STAND_SIZE) == false)
	{
		WindowOutDelete(this, m_map_x, m_map_y);//�폜����(��������)
		return;
	}

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);

	//��l���Ƃ���������
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		HeroHit();
	}


	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//��l���Ƃ̓����蔻��
void CObjNeedleStand::HeroHit()
{
	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);

	HIT_DATA** hit_data;	//�Փ˂̏�������\����
	hit_data = hit->SearchObjNameHit(OBJ_HERO);//�Փ˂̏���hit_data�ɓ����

	for (int i = 0; i < hit->GetCount(); i++)
	{
		if (hit_data[i] != nullptr)//�q�b�g�f�[�^�������
		{
			float r = hit_data[i]->r;//�������Ă���p�x�������Ă���

			//��l���I�u�W�F�N�g�������Ă���
			CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

			if (35.0f < r && r < 145.0f)
			{
				objhero->SetHitDown(true);//��l��������Ă�����m_hit_down��true��Ԃ�

				//�悹�鏈��
				objhero->SetPosY(m_py - 126.0f);//�u���b�N�̏㑤�ɒ��߂���

				//��l���̈ړ��x�N�g�����������Ȃ�
				if (objhero->GetVecY() > 0.0f)
					objhero->SetVecY(0.0f);//��l����Y�����̈ړ���0�ɂ���
			}
			//�������������Ă����
			else if (145.0f <= r && r <= 180.0f)
			{
				//���ɔ������鏈��
				objhero->SetPosX(m_px - -64.8f);//��l���̈ʒu���u���b�N�̍��ɂ���
				objhero->SetVecX(objhero->GetVecX());//��l����X�����̈ړ��ʂ𔽓]����
			}
			//�E�����������Ă����
			else if (0.0f <= r && r <= 35.0f)
			{
				//�E�ɔ������鏈��
				objhero->SetPosX(m_px + NEEDLE_STAND_SIZE);//��l���̈ʒu���u���b�N�̉E�ɂ���
				objhero->SetVecX(objhero->GetVecX());//��l����X�����̈ړ��ʂ𔽓]����
			}

			//�������������Ă����
			else if (180.0f < r && r < 360.0f)
			{
				//���ɔ������鏈��
				objhero->SetPosY(m_py + NEEDLE_STAND_SIZE);//��l���̈ʒu���u���b�N�̉��ɂ���
				objhero->SetVecY(objhero->GetVecY());//��l����Y�����̈ړ��ʂ𔽓]����
			}

		}
	}

}

//�h���[
void CObjNeedleStand::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + 64.0f;
	src.m_bottom = src.m_top + 64.0f;

	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + NEEDLE_STAND_SIZE;
	dst.m_bottom = dst.m_top + NEEDLE_STAND_SIZE;

	//�`��
	Draw::Draw(GRA_NEEDLE_STAND, &src, &dst, color, 0.0f);
}