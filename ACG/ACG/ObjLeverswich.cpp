#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjLeverSwich.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjLeverSwich::CObjLeverSwich(int x, int y)
{
	m_px = (float)x * LEVER_SWITCH_SIZE;
	m_py = (float)y * LEVER_SWITCH_SIZE;
}

//�C�j�V�����C�Y
void CObjLeverSwich::Init()
{
	m_ani_time = 0;
	m_ani_frame = 0;	//�Î~�t���[���������ɂ���
	m_ani_max_time = 4; //�A�j���[�V�����Ԋu��
	m_ani_flag = false;
	m_ani_flag2 = false;
	m_water_con = false;
	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, LEVER_SWITCH_SIZE, LEVER_SWITCH_SIZE, ELEMENT_GIMMICK, OBJ_LEVER_SWICH, 1);
}

//�A�N�V����
void CObjLeverSwich::Action()
{
	//���o�[�X�C�b�`��HitBox�X�V�p�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);

	//���[�v�Ƃ���������`���i�߂�
	if (hit->CheckObjNameHit(OBJ_ROPE) != nullptr)
	{
		Audio::Start(LEVER);
		
		//���̔����ON�ɂ���
		m_water_con = true;

		// �؂���]������----------------------------------
		m_wood_con = true;
		// ------------------------------------------------

		m_ani_time += 1;

		//�A�j���[�V�����̊��o�Ǘ�
		//�@���o�[�X�C�b�`�̕`�悪�����Ă��Ȃ���Ԃ̂Ƃ�
		if (m_ani_flag2 == false && m_ani_flag == false && m_ani_time > m_ani_max_time)
		{
			m_ani_frame += 1;
			m_ani_time = 0;
			m_ani_flag = true;
		}

		//�@���o�[�X�C�b�`�̕`�悪�����Ă����Ԃ̂Ƃ�
		else if (m_ani_flag2 == true && m_ani_flag == true && m_ani_time > m_ani_max_time)
		{
			
			m_ani_frame -= 1;
			m_ani_time = 0;
			m_ani_flag = false;
		}		
	}
	else
	{
		//���o�[�X�C�b�`�̕`�悪�����Ă��Ȃ���Ԃ̂Ƃ�
		if (m_ani_flag == true && m_ani_frame == 1)
			m_ani_flag2 = true;
		//���o�[�X�C�b�`�̕`�悪�����Ă����Ԃ̂Ƃ�
		else if (m_ani_flag == false && m_ani_frame == 0)
			m_ani_flag2 = false;
	}

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//�h���[
void CObjLeverSwich::Draw()
{
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
	src.m_top = 64.0f;
	src.m_left = (float)AniData[m_ani_frame] * 64.0f;
	src.m_right = src.m_left+64.0f;
	src.m_bottom = 128.0f;

	//�`��ʒu
	dst.m_top = 0.0f + m_py - objmap->GetScrollY();
	dst.m_left = 0.0f + m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + LEVER_SWITCH_SIZE;
	dst.m_bottom = dst.m_top + LEVER_SWITCH_SIZE;

	//�`��
	Draw::Draw(GRA_LEVER_SWICH, &src, &dst, color, 0);
}