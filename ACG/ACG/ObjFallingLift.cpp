//�g�p����w�b�_�[�t�@�C���@
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjFallingLift.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjFallingLift::CObjFallingLift(int x, int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjFallingLift::Init()
{
	//�����蔻��pHitBox���쐬                          
	Hits::SetHitBox(this, m_px, m_py, ROLL_BLOCK_SIZE_WIDTH, ROLL_BLOCK_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_FALLING_LIFT, 1);
}

//�A�N�V����
void CObjFallingLift::Action()
{
	//HitBox�̃|�C���^�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	//�q�[���[�I�u�W�F�N�g�Ɠ������Ă����
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		HeroRide();//�Փˏ��������������
	}
	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//�h���[
void CObjFallingLift::Draw()
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
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + ROLL_BLOCK_SIZE_WIDTH;
	dst.m_bottom = dst.m_top + ROLL_BLOCK_SIZE_HEIGHT;
		
	//�`��
	Draw::Draw(GRA_ROLL_BLOCK, &src, &dst, color, 0);
	
	
}

//��l�������������Ƃ��̏���
void CObjFallingLift::HeroRide()
{
	//��l���I�u�W�F�N�g�������Ă���
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//���g��HitBox�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	HIT_DATA** hit_data;										//�Փ˂̏�������\����
	hit_data = hit->SearchObjNameHit(OBJ_HERO);					//�Փ˂̏���hit_data�ɓ����

	for (int i = 0; i < hit->GetCount(); i++)
	{
		if (hit_data[i] != nullptr)								//�q�b�g�f�[�^�������
		{
			float r = hit_data[i]->r;							//�������Ă���p�x�������Ă���

			//�㑤���������Ă����
			if (35.0f < r && r < 145.0f)
			{
				objhero->SetHitDown(true);						//��l��������Ă�����m_hit_down��true��Ԃ�
			    //�悹�鏈��
				objhero->SetPosY(m_py - 126.0f);				//�u���b�N�̏㑤�ɒ��߂���

				//��l���̈ړ��x�N�g�����������Ȃ�
				if (objhero->GetVecY()>1.0f)
					objhero->SetVecY(1.0f);						//��l����Y�����̈ړ���0�ɂ���
			}
			//�������������Ă����
			else if (145.0f <= r && r <= 180.0f)
			{
				//���ɔ������鏈��
				objhero->SetPosX(m_px - HERO_SIZE_WIDTH+0.8f);	//��l���̈ʒu���u���b�N�̍��ɂ���
				objhero->SetVecX(-1.0f * objhero->GetVecX());	//��l����X�����̈ړ��ʂ𔽓]����
			}
			//�E�����������Ă����
			else if (0.0f <= r && r <= 35.0f )
			{
				//�E�ɔ������鏈��
				objhero->SetPosX(m_px + ROLL_BLOCK_SIZE_WIDTH);	//��l���̈ʒu���u���b�N�̉E�ɂ���
				objhero->SetVecX(-1.0f * objhero->GetVecX());	//��l����X�����̈ړ��ʂ𔽓]����
			}

			//�������������Ă����
			else if (180.0f < r && r < 360.0f)
			{
				//���ɔ������鏈��
				objhero->SetPosY(m_py + ROLL_BLOCK_SIZE_HEIGHT);//��l���̈ʒu���u���b�N�̉��ɂ���
				objhero->SetVecY(-1.0f * objhero->GetVecY());	//��l����Y�����̈ړ��ʂ𔽓]����
			}
		}
	}
}