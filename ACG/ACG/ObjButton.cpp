//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjButton.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjButton::CObjButton(float x, float y)
{
	m_Button_x = x;
	m_Button_y = y;
}

//�C�j�V�����C�Y
void CObjButton::Init()
{
	m_door_flag = false;

	//block�Ƃ̏Փˏ�Ԋm�F�p
	/*m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;*/

	//Hits::SetHitBox(this, m_x, m_y, 64, 12, ELEMENT_GREEN, OBJ_BUTTON, 1);
}

//�A�N�V����
void CObjButton::Action()
{
	////�u���b�N�^�C�v���m�p�̕ϐ����Ȃ����߂̃_�~�[
	//int d;

	////�u���b�N�Ƃ̓����蔻����s
	//CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//block->BlockHit(&m_x, &m_y, false,
	//	&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
	//	&d, OBJ_LIFT
	//);

	////�e�ƐڐG���Ă��邩�ǂ����𒲂ׂ�
	//if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	//{
	//	m_door_flag = true; //�e�Ƃ������Ă���Ȃ�true������
	//}

	////HitBox�̈ʒu�̕ύX
	//CHitBox* hit = Hits::GetHitBox(this);
	//hit->SetPos(m_x + block->GetScroll(), m_y + 2);
}

//�h���[
void CObjButton::Draw()
{
	////�A�j���[�V��������o�^
	//int AniData[2] =
	//{
	//	0 , 1
	//};

	////�`��J���[���
	//float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	//RECT_F src; //�`�挳�؂���ʒu
	//RECT_F dst; //�`���\���ʒu

	//			//�؂���ʒu�̐ݒ�
	//src.m_top = 0.0f;
	//src.m_left = AniData[m_ani_frame] * 64.0f;
	//src.m_right = src.m_left + 64.0f;
	//src.m_bottom = 64.0f;

	////�u���b�N���������Ă���
	//CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	////�\���ʒu�̐ݒ�
	//dst.m_top = -16.0f + m_y;
	//dst.m_left = -12.0f + m_x + block->GetScroll();
	//dst.m_right = 78.0f + m_x + block->GetScroll();
	//dst.m_bottom = 50.0f + m_y;

	////�`��
	//Draw::Draw(28, &src, &dst, c, 0.0f);
}