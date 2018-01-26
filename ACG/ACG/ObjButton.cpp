//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjButton.h"
#include "Function.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjButton::CObjButton(int x, int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
	m_map_x = x;
	m_map_y = y;
}

//�C�j�V�����C�Y
void CObjButton::Init()
{
	m_trick_flag = false;

	m_ani_time = 0;
	m_ani_frame = 0;  //�Î~�t���[���������ɂ���
	m_ani_max_time = 8; //�A�j���[�V�����Ԋu��
	m_ani_start_flag = false;//�A�j���t���OOFF
	m_callout_time = 0;
	//�����蔻��
	Hits::SetHitBox(this, m_px, m_py, 36, 32, ELEMENT_GIMMICK, OBJ_BUTTON, 1);
}

//�A�N�V����
void CObjButton::Action()
{
	// �{�^���������ꂽ��
	if (m_trick_flag == true)
	{
		m_ani_start_flag = true; // �t���O�I��
		m_callout_time++;
	}
	HitBox* hit = Hits::GetHitBox(this);
	
	// �e�ƐڐG���Ă��邩�ǂ����𒲂ׂ�
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{
		m_trick_flag = true; //�e�Ƃ������Ă���Ȃ�true������
	}

	//�A�j���t���OON����
	if (m_ani_start_flag == true && m_ani_frame != 1)
	{
		m_ani_time += 1;

		//�A�j���[�V�����̊��o�Ǘ�
		if (m_ani_time > m_ani_max_time)
		{
			m_ani_frame += 1;
			m_ani_time = 0;
		}

		//�Ō�܂ŃA�j���[�V�������i�ނƑ��݂�����
		if (m_ani_frame == 1)
		{
			m_ani_frame = 1;
			return;
		}
		Audio::Start(BUTTON);

	}

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px+13.0f, m_py);
}

//�h���[
void CObjButton::Draw()
{
	//��l���I�u�W�F�N�g�������Ă���
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//�摜�̐؂���z��
	int AniData[2] =
	{
		0  , 1 ,
	};

	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = AniData[m_ani_frame] * BUTTON_SIZE;
	src.m_right = src.m_left+BUTTON_SIZE;
	src.m_bottom = src.m_top + BUTTON_SIZE;

	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + BUTTON_SIZE;
	dst.m_bottom = dst.m_top + BUTTON_SIZE;

	//�`��
	Draw::Draw(GRA_BUTTON, &src, &dst, color, 0.0f);

	if (m_callout_time>0&&m_callout_time < 300)
	{
		//�؂���ʒu
		src.m_top = 0.0f;
		src.m_left = 296.0f;
		src.m_right = 593.0f;
		src.m_bottom = 128.0f;

		//�`��ʒu
		dst.m_top =   objhero->GetPosY()- objmap->GetScrollY() -128.0f;
		dst.m_left =  objhero->GetPosX()- objmap->GetScrollX()-128.0f;
		dst.m_right = dst.m_left + 300.0f;
		dst.m_bottom = dst.m_top + SIGN_SIZE*4.0f;
		//�`��
		Draw::Draw(GRA_SIGN_FRAME, &src, &dst, color, 0.0f);
	}
}