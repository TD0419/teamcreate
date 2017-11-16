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
}

//�C�j�V�����C�Y
void CObjDoor::Init()
{
	m_ani_door_time = 0;
	m_ani_door_frame = 1;	 //�Î~�t���[��������������
	m_ani_door_time_max = 20;//�A�j���[�V�����Ԋu��

	m_unlock_flag = false;
	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, DOOR_SIZE, DOOR_SIZE, ELEMENT_GIMMICK, OBJ_DOOR, 1);
}

//�A�N�V����
void CObjDoor::Action()
{
	//�h�A��HitBox�X�V�p�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);

	//�{�X�̏����ĂԂ�
	CObjBoss*objboss = (CObjBoss*)Objs::GetObj(OBJ_BOSS);


	//�{�X�����ł����Ƃ�
	if (objboss==nullptr)
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
		if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
		{
			//�X�e�[�W�J�E���g�𑝂₵�Ď��̃X�e�[�W�ɂ���
			((UserData*)Save::GetData())->stagenum += 1;
			Scene::SetScene(new CSceneMain());
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