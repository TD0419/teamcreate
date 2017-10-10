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
	m_px = x * 64;
	m_py = y * 64;
}

//�C�j�V�����C�Y
void CObjLastWall::Init()
{
	m_ani_time = 0;
	m_ani_frame = 1;  //�Î~�t���[���������ɂ���
	m_ani_max_time = 17; //�A�j���[�V�����Ԋu��
	m_ani_start = false;

	//�����蔻��																
	Hits::SetHitBox(this, m_px, m_py, WATER_SIZE_WIDTH, WATER_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_WATER, 1);
	m_water_gauge = 0.0f;
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
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + 96;
	dst.m_bottom = dst.m_top + 512;

	//�`��(��̕���)
	Draw::Draw(22, &src, &dst, color, 0.0f);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY()+467;
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + 96;
	dst.m_bottom = dst.m_top + 185;
	//�`��(���̕���)
	Draw::Draw(21, &src, &dst, color, 0.0f);
}