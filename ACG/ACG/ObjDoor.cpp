#include "GameL\DrawTexture.h"
#include "GameL\UserData.h"
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
	m_map_x=x;	
	m_map_y=y;
}

//�C�j�V�����C�Y
void CObjDoor::Init()
{
	m_ani_door_time = 0;
	m_ani_door_frame = 1;	 //�Î~�t���[��������������
	m_ani_door_time_max = 20;//�A�j���[�V�����Ԋu��

	m_unlock_flag = false;

	m_goal_flag = false;	// true:�S�[������ false:�S�[�����Ă��Ȃ�

	switch (((UserData*)Save::GetData())->stagenum)
	{
		//�X�e�[�W�P
	case 1:
		m_door_type = 1;
		break;
		//�X�e�[�W�Q
	case 2:
		m_door_type = 2;
		break;
		//�X�e�[�W�R
	case 3:
		m_door_type = 3;
		break;
		//�X�e�[�W�T
	case 5:
		m_door_type = 5;
		break;
	default:

		break;
	}

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, DOOR_SIZE, DOOR_SIZE, ELEMENT_GIMMICK, OBJ_DOOR, 1);
}

//�A�N�V����
void CObjDoor::Action()
{
	//��ʊO�Ȃ�
	if (WindowCheck(m_px, m_py, DOOR_SIZE, DOOR_SIZE) == false)
	{
		WindowOutDelete(this, m_map_x, m_map_y);//�폜����(��������)
		return;
	}

	//�h�A��HitBox�X�V�p�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);

	//�{�X�̏����ĂԂ�
	CObjBoss*objboss = (CObjBoss*)Objs::GetObj(OBJ_BOSS);
	CObjEnemy*objenemy = (CObjEnemy*)Objs::GetObj(OBJ_ENEMY);
	CObjStage5Boss* objstage5_boss = (CObjStage5Boss*)Objs::GetObj(OBJ_STAGE5_BOSS);
	switch (m_door_type)
	{
	case 1:
		if (objenemy == nullptr)
		{
			m_unlock_flag = true;//�{�������t���O��on�ɂ��܂�
		}
		break;
	case 2:
		//�{�X�����ł����Ƃ�
		if (objboss == nullptr)
		{
			m_unlock_flag = true;//�{�������t���O��on�ɂ��܂�
		}
		break;
	case 5:
		//�X�e�[�W�T�̃{�X�����ł����Ƃ�
		if (objstage5_boss == nullptr)
		{
			m_unlock_flag = true;//�{�������t���O��on�ɂ��܂�
		}
		break;
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
		if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
		{
			if (m_goal_flag == false)// �܂��S�[���t���O�������Ă��Ȃ��ꍇ
			{
				// ��l���I�u�W�F�N�g�������Ă���
				CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);
				// �S�[���t���O�𗧂Ă�
				objhero->HeroGoal();
				m_goal_flag = true;
			}
		}
	}
	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
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