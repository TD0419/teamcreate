//�g�p����w�b�_�[�t�@�C���@
#include "GameL\HitBoxManager.h"
#include "GameL\WinInputs.h"
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
	m_px = x *  WATER_SIZE_WIDTH;
	m_py = y * WATER_SIZE_HEIGHT;
}

//�C�j�V�����C�Y
void CObjWater::Init()
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
void CObjWater::Action()
{
	m_ani_time += 1;

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);
	
	int map_num= obj_m->GetMap(m_map_x , m_map_y - 1);
	
	//1��̃}�X�����Ȃ�
 	if( map_num == MAP_WATER)
	{
		return;
	}

	//�A�j���[�V�������J�n����̂Ńt���O���I���ɂ���
	m_ani_start = true;

	// m_water_gauge��64���z�����珈���X�g�b�v
	if (m_water_gauge >= WATER_SIZE_HEIGHT)
	{
		Hits::DeleteHitBox(this);//hitbox�폜
		obj_m->SetMap(m_map_x, m_map_y, MAP_SPACE);//�}�b�v�̐��l����ɂ���
		this->SetStatus(false);//���g
		return;
	}
	else
	{
		m_water_gauge += 0.2f; // 1�����₵�Ă���
		// hitbox���������Ȃ�
        hit->SetPos(m_px - obj_m->GetScrollX(), m_py - obj_m->GetScrollY() + m_water_gauge, WATER_SIZE_HEIGHT - m_water_gauge, WATER_SIZE_WIDTH);


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
	
}
//�h���[
void CObjWater::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = AniData[m_ani_frame] * WATER_SIZE_WIDTH;
	src.m_right = src.m_left+WATER_SIZE_WIDTH;
	src.m_bottom = src.m_top+WATER_SIZE_HEIGHT;

	//�`��ʒu
	dst.m_top = m_py + m_water_gauge - obj_m->GetScrollY();
	dst.m_left = m_px - obj_m->GetScrollX();
	dst.m_right = dst.m_left + BLOCK_SIZE;
	dst.m_bottom = dst.m_top + WATER_SIZE_HEIGHT - m_water_gauge;

	
	if(m_ani_start==false)
		Draw::Draw(12, &src, &dst, color, 0);//���i�g�Ȃ��̉摜�j
	else
		Draw::Draw(11, &src, &dst, color, 0);//���i�g�L�̉摜�@�A�j���[�V�����t���j
}