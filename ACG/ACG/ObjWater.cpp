//�g�p����w�b�_�[�t�@�C���@
#include "GameL\HitBoxManager.h"
#include "GameL\WinInputs.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "ObjWater.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjWater::CObjWater(int x, int y)
{
	m_map_x = x;
	m_map_y = y;
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjWater::Init()
{
	m_ani_time = 0;
	m_ani_frame = 0;  //�Î~�t���[���������ɂ���
	m_ani_max_time = 17; //�A�j���[�V�����Ԋu��
	m_ani_start = false;

	//�����蔻��																
	Hits::SetHitBox(this, m_px, m_py, WATER_SIZE_WIDTH, WATER_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_WATER, 1);
	m_water_gauge = 0.0f;
}

//�A�N�V����
void CObjWater::Action()
{
	m_ani_time += 1;

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);

	//���o�[�X�C�b�`�I�u�W�F�N�g�������Ă���
	CObjLeverSwich* obj_lever = (CObjLeverSwich*)Objs::GetObj(OBJ_LEVER_SWICH);

	bool lever_swich = false;
	//���o�[�X�C�b�`�I�u�W�F�N�g���������Ă��邩�ǂ����𒲂ׂ�
	if (obj_lever != nullptr)
		lever_swich = obj_lever->GetWater();
	else
		lever_swich = false;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�A�j���[�V�������J�n����̂Ńt���O���I���ɂ���
	m_ani_start = true;
	
	// m_water_gauge��192���z�����珈���X�g�b�v
	if (m_water_gauge >= WATER_SIZE_HEIGHT)
	{
		Hits::DeleteHitBox(this);//hitbox�폜
		objmap->SetMap(m_map_x, m_map_y, MAP_SPACE);//�}�b�v�̐��l����ɂ���
		this->SetStatus(false);//���g
		return;
	}
	else
	{
		//���o�[�X�C�b�`��������Ă�����
		if (lever_swich == true)
		{
			m_water_gauge += 0.2f; // 1�����₵�Ă���
		}
	}

	// hitbox���������Ȃ�
	hit->SetPos(m_px - objmap->GetScrollX(), m_py - objmap->GetScrollY() + m_water_gauge, WATER_SIZE_WIDTH, WATER_SIZE_HEIGHT - m_water_gauge);

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
}
//�h���[
void CObjWater::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 0.0f + WATER_SIZE_HEIGHT * m_ani_frame;
	src.m_left =0.0f;
	src.m_right = src.m_left+WATER_SIZE_WIDTH;
	src.m_bottom =src.m_top+WATER_SIZE_HEIGHT;

	//�`��ʒu
	dst.m_top = m_py + m_water_gauge - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + WATER_SIZE_WIDTH;
	dst.m_bottom = dst.m_top + WATER_SIZE_HEIGHT - m_water_gauge;

	Draw::Draw(GRA_AQUATIC, &src, &dst, color, 0);//��
}