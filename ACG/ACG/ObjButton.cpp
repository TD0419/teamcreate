//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

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
}

//�C�j�V�����C�Y
void CObjButton::Init()
{
	m_trick_flag = false;

	m_ani_time = 0;
	m_ani_frame = 0;  //�Î~�t���[���������ɂ���
	m_ani_max_time = 8; //�A�j���[�V�����Ԋu��
	m_ani_start_flag = false;//�A�j���t���OOFF
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
	}
	HitBox* hit = Hits::GetHitBox(this);
	
	// �e�ƐڐG���Ă��邩�ǂ����𒲂ׂ�
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{
		m_trick_flag = true; //�e�Ƃ������Ă���Ȃ�true������

	}

	//�A�j���t���OON����
	if (m_ani_start_flag == true&&m_ani_frame!=1)
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
	}

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px+13, m_py);

}

//�h���[
void CObjButton::Draw()
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
	src.m_top = 0.0f;
	src.m_left = AniData[m_ani_frame] * BUTTON_SIZE;
	src.m_right = src.m_left+BUTTON_SIZE;
	src.m_bottom = src.m_top + BUTTON_SIZE;

	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY()-16;
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + BUTTON_SIZE;
	dst.m_bottom = dst.m_top + BUTTON_SIZE;

	
	//�`��
	Draw::Draw(20, &src, &dst, color, 0.0f);
}