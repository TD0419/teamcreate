//�g�p����w�b�_�[�t�@�C���@
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
	m_get_on_flag = false;		//false�c��l��������Ă��Ȃ�  true�c��l��������Ă���
	//�����蔻��pHitBox���쐬                          
	Hits::SetHitBox(this, m_px, m_py, ROLL_BLOCK_SIZE_WIDTH, ROLL_BLOCK_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_FALLING_LIFT, 1);
}

//�A�N�V����
void CObjFallingLift::Action()
{
	//HitBox�̃|�C���^�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	//��l�����������Ă���&&��l�������t�g�̏�ɗ����ĂȂ��Ƃ�
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr&&m_get_on_flag == false)
	{
		HeroRide();//�Փˏ���������
	}
	//��l�����������Ă���&&��l�������t�g�̏�ɗ����Ă鎞
	else if (hit->CheckObjNameHit(OBJ_HERO) != nullptr&&m_get_on_flag == true)
	{
		m_py += 5.0f;	//�����郊�t�g���ړ�(��������)
		HeroRide();//�Փˏ���������
	}

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(hit, m_px, m_py);
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
	Draw::Draw(GRA_FALLING_LIFT, &src, &dst, color, 0.0f);
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
			if (31.0f < r && r < 145.5f)
			{
				m_get_on_flag = true;							//�u��l��������Ă���v�Ǝ��ʂ���B
				objhero->SetHitDown(true);						//��l��������Ă�����m_hit_down��true��Ԃ�
			    //�悹�鏈��
				objhero->SetPosY(m_py - HERO_SIZE_HEIGHT + 2.5f);//��l���̃|�W�V���������t�g�̏�ɂ���
				objhero->SetVecY(4.0f);							//��l����Y�����̈ړ���3�ɂ���
			}
			//�������������Ă����
			if (145.5f <= r && r <= 210.0f)
			{
				m_get_on_flag = false;							//�u��l���͏���Ă��Ȃ��v�Ǝ��ʂ���B
				//��l�����E�������Ă���Ƃ�
				if (objhero->GetPosture() == 0.0f)
				{
					//���ɔ������鏈��
					objhero->SetPosX(m_px - 49.0f);	//��l���̈ʒu���u���b�N�̍��ɂ���
					objhero->SetVecX(0.0f);//��l����X�����̈ړ����O�ɂ���
				}
				//��l�����������Ă��鎞
				else
				{
					//���ɔ������鏈��
					objhero->SetPosX(m_px - 62.0f);	//��l���̈ʒu���u���b�N�̍��ɂ���
					objhero->SetVecX(0.0f);//��l����X�����̈ړ����O�ɂ���
				}
			}
			//�E�����������Ă����
			if (0.0f <= r && r <= 31.0f||335.0f<r&&r<360.0f )
			{
				if (objhero->GetPosture() == 1.0f)
				{
					m_get_on_flag = false;//�u��l���͏���Ă��Ȃ��v�Ǝ��ʂ���B
					//�E�ɔ������鏈��
					objhero->SetPosX(m_px + 177.0f);//��l���̈ʒu���u���b�N�̉E�ɂ���
					objhero->SetVecX(0.0f);//��l����X�����̈ړ����O�ɂ���
				}
				else
				{
					m_get_on_flag = false;//�u��l���͏���Ă��Ȃ��v�Ǝ��ʂ���B
					//�E�ɔ������鏈��
					objhero->SetPosX(m_px + 190.0f);	//��l���̈ʒu���u���b�N�̉E�ɂ���
					objhero->SetVecX(0.0f);//��l����X�����̈ړ����O�ɂ���
				}
			}
			
			//�������������Ă����
			if (210.0f < r && r < 335.0f)
			{
				m_get_on_flag = false;							//�u��l���͏���Ă��Ȃ��v�Ǝ��ʂ���B
				//���ɔ������鏈��
				objhero->SetPosY(m_py + 49.5f);//��l���̈ʒu���u���b�N�̉��ɂ���
				objhero->SetVecY(0.0f);//��l����Y�����̈ړ����O�ɂ���
			}
		}
	}
}