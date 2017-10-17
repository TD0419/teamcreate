#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjLastWall.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjLastWall::CObjLastWall(int x, int y)
{
	m_px = (float)x * 64.0f;
	m_py = (float)y * 64.0f;
}

//�C�j�V�����C�Y
void CObjLastWall::Init()
{
	m_ani_time = 0;
	m_ani_frame = 1;  //�Î~�t���[���������ɂ���
	m_ani_max_time = 17.0f; //�A�j���[�V�����Ԋu��
	m_ani_start = false;

	//�����蔻��																
	Hits::SetHitBox(this, m_px, m_py, 32, 512, ELEMENT_GIMMICK, OBJ_LAST_WALL, 1);
}

//�A�N�V����
void CObjLastWall::Action()
{
	m_ani_time += 1;

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);

	//	//�A�j���[�V�����̊��o�Ǘ�
	//	if (m_ani_time > m_ani_max_time)
	//	{
	//		m_ani_frame += 1;
	//		m_ani_time = 0;
	//	}

	//	//�Ō�܂ŃA�j���[�V�������i�ނƍŏ��ɖ߂�
	//	if (m_ani_frame == 2)
	//	{
	//		m_ani_frame = 0;
	//	}
	//}

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px+27, m_py+195);
}

//�h���[
void CObjLastWall::Draw()
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
	dst.m_top = m_py - objmap->GetScrollY()-60;
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + 96.0f;
	dst.m_bottom = dst.m_top + 256.0f;

	//�`��(��̕���)
	Draw::Draw(22, &src, &dst, color, 0.0f);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 640.0f;

	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY()+195;
	dst.m_left = m_px - objmap->GetScrollX()+30;
	dst.m_right = dst.m_left + 32;
	dst.m_bottom = dst.m_top + 512;
	//�`��(���̕���)
	Draw::Draw(21, &src, &dst, color, 0.0f);
}

void CObjLastWall::HeroHit(float px,float py)
{
	//���g��HitBox�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

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

									 //�u���b�N�̉E�����Փ˂��Ă���ꍇ
			if (0 < r && r < 45 || 315 < r && r < 360)
			{
				objhero->SetVecX(0.0f);//��l����X�����̈ړ����O�ɂ���
				objhero->SetPosX(px + 32.0f);//��l���̈ʒu��؂̉E���܂ł��炷
			}
			//�u���b�N�̏㑤���Փ˂��Ă���ꍇ
			else if (45 < r && r < 125)
			{

				objhero->SetVecY(0.0f);//��l����Y�����̈ړ����O�ɂ���
				objhero->SetPosY(py - HERO_SIZE_HEIGHT);//��l���̈ʒu��؂̏㑤�܂ł��炷
			}
			//�u���b�N�̍������Փ˂��Ă���ꍇ
			else if (125 < r && r < 225)
			{
				objhero->SetVecX(0.0f);//��l����X�����̈ړ����O�ɂ���
				objhero->SetPosX(px - HERO_SIZE_WIDTH);//��l���̈ʒu��؂̍����܂ł��炷
			}
			//�u���b�N�̉������Փ˂��Ă���ꍇ
			else if (225 < r && r < 315)
			{
				objhero->SetVecY(0.0f);//��l����Y�����̈ړ����O�ɂ���
				objhero->SetPosY(py + WOOD_SIZE);//��l���̈ʒu��؂̉����܂ł��炷
			}
		}
	}
}