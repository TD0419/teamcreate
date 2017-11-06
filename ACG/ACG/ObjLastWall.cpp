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
	//�����蔻��																
	Hits::SetHitBox(this, m_px, m_py, 32, 512, ELEMENT_GIMMICK, OBJ_LAST_WALL, 1);
	m_wall_gauge = 0.0f;
	m_look_unlock_flag = false;
}

//�A�N�V����
void CObjLastWall::Action()
{
	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	HIT_DATA** hit_data;	//�Փ˂̏�������\����
	hit_data = hit->SearchObjNameHit(OBJ_HERO);//�Փ˂̏���hit_data�ɓ����

	//��l���I�u�W�F�N�g�������Ă���
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	// �{�^���I�u�W�F�N�g�������Ă���
	CObjButton* objbutton = (CObjButton*)Objs::GetObj(OBJ_BUTTON);
	//�{�^���������Ă�������J���t���O�I��
	if (objbutton->GetTrickFlag() == true)
		m_look_unlock_flag = true;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);
	int map_num = objmap->GetMap(m_map_x, m_map_y);

	// m_wall_gauge��512���z�����珈���X�g�b�v
	if (m_wall_gauge >= 512)
	{
		return;
	}
	else
	{//���o�[�X�C�b�`��������Ă�����
		if (m_look_unlock_flag == true)
		{
			m_wall_gauge += 1; // 1�����₵�Ă���
		}
	}

	// hitbox���������Ȃ�
	hit->SetPos(m_px - objmap->GetScrollX(), m_py - objmap->GetScrollY() + m_wall_gauge, 512 - m_wall_gauge, 32);

	for (int i = 0; i < hit->GetCount(); i++)
	{
		//�f�[�^�������
		if (hit_data[i] != nullptr)
		{
			float r = hit_data[i]->r;//�������Ă���p�x�������Ă���

									 //LastWall�̉E�����Փ˂��Ă���ꍇ
			if (0 < r && r < 85 || 275 < r && r < 360)
			{
				objhero->SetVecX(0.0f);//��l����X�����̈ړ����O�ɂ���
				objhero->SetPosX(m_px + 62.0f);//��l���̈ʒu��LastWall�̉E���܂ł��炷
			}

			//LastWall�̏㑤���Փ˂��Ă���ꍇ
			else if (85 < r && r < 94)
			{

				objhero->SetVecY(0.0f);//��l����Y�����̈ړ����O�ɂ���
				objhero->SetPosY(m_py-60.0f);//��l���̈ʒu��LastWall�̏㑤�܂ł��炷
			}

			//LastWall�̍������Փ˂��Ă���ꍇ
			else if (94 < r && r < 266)
			{
				objhero->SetVecX(0.0f);//��l����X�����̈ړ����O�ɂ���
				objhero->SetPosX(m_px - HERO_SIZE_WIDTH+28.0f);//��l���̈ʒu��LastWall�̍����܂ł��炷
			}

			//LastWall�̉������Փ˂��Ă���ꍇ
			else if (266 < r && r < 275)
			{
				objhero->SetVecY(0.0f);//��l����Y�����̈ړ����O�ɂ���
				objhero->SetPosY(m_py + 512.0f);//��l���̈ʒu��LastWall�̉����܂ł��炷
			}
		}
	}
	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px+29, m_py+65);
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
	src.m_bottom = 256.0f;

	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY() - 190;
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + 96.0f;
	dst.m_bottom = dst.m_top + 256.0f;

	//�`��(��̕���)
	Draw::Draw(21, &src, &dst, color, 0.0f);

	//-----------------------------------------------------
	if (m_wall_gauge != 512)
	{
		//�؂���ʒu
		src.m_top = 0.0 + m_wall_gauge;
		src.m_left = 0.0f;
		src.m_right = 32.0f;
		src.m_bottom = 512.0f;
	}
	//�`��ʒu
	dst.m_top = m_py  - objmap->GetScrollY() + 65;
	dst.m_left = m_px - objmap->GetScrollX() + 30;
	dst.m_right = dst.m_left + 32;
	dst.m_bottom = dst.m_top + 512 - m_wall_gauge;
	//�`��(���̕���)
	Draw::Draw(22, &src, &dst, color, 0.0f);
}
