#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjLeverSwich.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjLeverSwich::CObjLeverSwich(float x, float y)
{
	m_px = x * LEVER_SWITCH_SIZE;
	m_py = y * LEVER_SWITCH_SIZE;
}

//�C�j�V�����C�Y
void CObjLeverSwich::Init()
{
	m_ani_time = 0;
	m_ani_frame = 0;	//�Î~�t���[���������ɂ���
	m_ani_max_time = 4; //�A�j���[�V�����Ԋu��
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
		//���̔����ON�ɂ���
		m_water_con = true;

		m_ani_time += 1;

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

		// �؂���]������----------------------------------
		
		// �؃I�u�W�F�N�g�������Ă���
		CObjWood* obj_wood = (CObjWood*)Objs::GetObj(OBJ_WOOD);

		// �؂ɉ�]�t���O�𗧂Ă�
		if (obj_wood != nullptr)
			obj_wood->Rotation(true);

		// ------------------------------------------------
		
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
	src.m_top = 0.0f;
	src.m_left = AniData[m_ani_frame] * 64;
	src.m_right = 64.0f + AniData[m_ani_frame] * 64;
	src.m_bottom = 64.0f;

	//�`��ʒu
	dst.m_top = 0.0f + m_py - objmap->GetScrollY();
	dst.m_left = 0.0f + m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + LEVER_SWITCH_SIZE;
	dst.m_bottom = dst.m_top + LEVER_SWITCH_SIZE;

	//�`��
	Draw::Draw(9, &src, &dst, color, 0);
}