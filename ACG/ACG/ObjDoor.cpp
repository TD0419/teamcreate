#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjDoor.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjDoor::CObjDoor(int x, int y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjDoor::Init()
{
	m_ani_door_time = 0;
	m_ani_door_frame = 1;	 //�Î~�t���[��������������
	m_ani_door_time_max = 20;//�A�j���[�V�����Ԋu��

	m_unlock_flag = false;
}

//�A�N�V����
void CObjDoor::Action()
{
	//�{�X�̏����ĂԂ�
	CObjBoss*objboss = (CObjBoss*)Objs::GetObj(OBJ_BOSS);
	bool boss_delete;
	//�{�X�����Ȃ��Ȃ�����B
	if (objboss != nullptr)
	{
		boss_delete = objboss->GetDieFlag();//boss_delete�ɏ�������B
	}
	else
	{
		boss_delete = false;//�{�X�͂��܂�
	}
	//�{�X�����ł����Ƃ�
	if (boss_delete == true)
	{
		m_unlock_flag = true;//�{�������t���O��on�ɂ��܂�
	}

	//�{�������t���O�I���̂Ƃ�
	if (m_unlock_flag==true)
	{
		m_ani_door_time += 1;//�A�j���[�V�����^�C��+�P
	}
	//�h�A�A�j���^�C�����}�b�N�X�^�C����菭�Ȃ��A�t���[����2����Ȃ��Ƃ�
	if (m_ani_door_time > m_ani_door_time_max&&m_ani_door_frame != 2)
	{
		m_ani_door_frame += 1;//�h�A�̃t���[����+1���܂��B
		m_ani_door_time = 0;  //�h�A�^�C����0�ɂ��܂�
		Audio::Start(DOOR);//�h�A���y�X�^�[�g
	}
	//�h�A�t���[����2�̂Ƃ�
	if (m_ani_door_frame == 2)
		
	{
		m_ani_door_frame = 2;//�t���[����2�ɌŒ�
		return;
	}
}

//�h���[
void CObjDoor::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = m_ani_door_frame * 128.0f-128.0f;
	src.m_right = src.m_left+128.0f;
	src.m_bottom = src.m_top+128.0f;

	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + DOOR_SIZE;
	dst.m_bottom = dst.m_top + DOOR_SIZE;

	//�`��
	Draw::Draw(GRA_DOOR, &src, &dst, color, 0.0f);
}