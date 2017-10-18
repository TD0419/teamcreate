//�g�p����w�b�_�[�t�@�C���@
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjRock.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjRock::CObjRock(int x, int y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjRock::Init()
{
	m_ani_time = 0;
	m_ani_frame = 1;  //�Î~�t���[���������ɂ���
	m_ani_max_time = 8; //�A�j���[�V�����Ԋu��
	m_ani_start_flag = false;//�A�j���t���OOFF

	//�����蔻��pHitBox���쐬                          
	Hits::SetHitBox(this, m_px, m_py, ROCK_SIZE_WIDTH, ROCK_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_ROCK, 1);
}

//�A�N�V����
void CObjRock::Action()
{
	//�u���b�N���������Ă���
	CObjBlock* objblock = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	
	//�e�ƐڐG���Ă��邩�ǂ����𒲂ׂ�
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{
		m_ani_start_flag = true;//�A�j���t���OON
	}
	//�A�j���t���OON����
	if (m_ani_start_flag == true)
	{
		m_ani_time+=1;
		//�A�j���[�V�����̊��o�Ǘ�
		if (m_ani_time > m_ani_max_time)
		{
			m_ani_frame += 1;
			m_ani_time = 0;
		}

		//�Ō�܂ŃA�j���[�V�������i�ނƑ��݂�����
		if (m_ani_frame == 4)
		{
			Hits::DeleteHitBox(this);	//�₪���L����HitBox�ɍ폜����
			this->SetStatus(false);		//���g�ɍ폜���߂��o��
			return;
		}
	}

	HIT_DATA** hit_data;	//�Փ˂̏�������\����
	hit_data = hit->SearchObjNameHit(OBJ_HERO);//�Փ˂̏���hit_data�ɓ����

	//��l���I�u�W�F�N�g�������Ă���
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	for (int i = 0; i < hit->GetCount(); i++)
	{
		//�f�[�^�������
		if (hit_data[i] != nullptr)
		{
			float r = hit_data[i]->r;//�������Ă���p�x�������Ă���

			//��̉E�����Փ˂��Ă���ꍇ
			if (0 < r && r < 65|| 315 < r && r < 360)
			{
				objhero->SetVecX(0.0f);//��l����X�����̈ړ����O�ɂ���
				objhero->SetPosX(m_px + ROCK_SIZE_WIDTH);//��l���̈ʒu����̉E���܂ł��炷
			}
			
			//��̏㑤���Փ˂��Ă���ꍇ
			else if (65 < r && r < 125)
			{

				objhero->SetVecY(0.0f);//��l����Y�����̈ړ����O�ɂ���
				objhero->SetPosY(m_py - ROCK_SIZE_HEIGHT-57.0);//��l���̈ʒu����̏㑤�܂ł��炷
				
			}

			//��̍������Փ˂��Ă���ꍇ
			else if (125 < r && r < 225 )
			{
				objhero->SetVecX(0.0f);//��l����X�����̈ړ����O�ɂ���
				objhero->SetPosX(m_px - HERO_SIZE_WIDTH);//��l���̈ʒu����̍����܂ł��炷
			}

			//��̉������Փ˂��Ă���ꍇ
			else if (225 < r && r < 315)
			{
				objhero->SetVecY(0.0f);//��l����Y�����̈ړ����O�ɂ���
				objhero->SetPosY(m_py + ROCK_SIZE_HEIGHT);//��l���̈ʒu����̉����܂ł��炷
			}
		}
	}

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py- ROCK_SIZE_WIDTH);

}

//�h���[
void CObjRock::Draw()
{
	//�摜�̐؂���z��
	int AniData[4] =
	{
		0, 1, 2, 3
	};

	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 1.0f;
	src.m_left = AniData[m_ani_frame] * BLOCK_SIZE - BLOCK_SIZE;
	src.m_right = src.m_left + BLOCK_SIZE;
	src.m_bottom = src.m_top + BLOCK_SIZE;
	
	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY()- ROCK_SIZE_WIDTH;
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + ROCK_SIZE_WIDTH;
	dst.m_bottom = dst.m_top + ROCK_SIZE_HEIGHT;

	
	//�`��
	Draw::Draw(10, &src, &dst, color, 0.0f);
}