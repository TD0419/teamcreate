//�g�p����w�b�_�[�t�@�C���@
#include "GameL\HitBoxManager.h"
#include "GameHead.h"
#include "ObjWater.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjWater::CObjWater(int x, int y)
{
	m_px = x * WATER_SIZE_WIDTH;
	m_py = y * WATER_SIZE_HEIGHT;
}

//�C�j�V�����C�Y
void CObjWater::Init()
{
	m_ani_time = 0;
	m_ani_frame = 1;  //�Î~�t���[���������ɂ���
	m_ani_max_time = 17; //�A�j���[�V�����Ԋu��

	//�����蔻��
	Hits::SetHitBox(this, m_px, m_py, WATER_SIZE_WIDTH, WATER_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_WATER, 1);
}

//�A�N�V����
void CObjWater::Action()
{
	m_ani_time += 1;

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);

	//�A�j���[�V�����̊��o�Ǘ�
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	//�Ō�܂ŃA�j���[�V�������i�ނƍŏ��ɖ߂�
	if (m_ani_frame == 2)
	{
		m_ani_frame = 0;
	}

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//�h���[
void CObjWater::Draw()
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
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * 128;
	src.m_right = 128.0f + AniData[m_ani_frame] * 128;
	src.m_bottom = 64.0f;

	//�`��ʒu
	dst.m_top = 0.0f + m_py - obj_m->GetScrollY();
	dst.m_left = 0.0f + m_px - obj_m->GetScrollX();
	dst.m_right = dst.m_left + WATER_SIZE_WIDTH;
	dst.m_bottom = dst.m_top + WATER_SIZE_HEIGHT;

	//�`��
	Draw::Draw(11, &src, &dst, color, 0);
}