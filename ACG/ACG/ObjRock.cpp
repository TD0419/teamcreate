//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjRock.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjRock::CObjRock(float x, float y)
{
	m_x = x;
	m_y = y;
}

//�C�j�V�����C�Y
void CObjRock::Init()
{
	//m_ani_time = 60;
	//m_ani_frame = 1;  //�Î~�t���[���������ɂ���
	//m_ani_max_time = 4; //�A�j���[�V�����Ԋu��

	//Hits::SetHitBox(this, m_x, m_y, 64, 64, ELEMENT_GREEN, OBJ_ROCK, 1);
}

//�A�N�V����
void CObjRock::Action()
{


	//////�e�ƐڐG���Ă��邩�ǂ����𒲂ׂ�
	//if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	//{
	//	//�₪����A�j���[�V����������

	//	//----//

	//	this->SetStatus(false);		//���g�ɍ폜���߂��o��
	//	Hits::DeleteHitBox(this);	//�G�����L����HitBox�ɍ폜����
	//}

	//�u���b�N���������Ă���
	//CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	////HitBox�̈ʒu�̕ύX
	//CHitBox* hit = Hits::GetHitBox(this);
	//hit->SetPos(m_x + block->GetScroll(), m_y + 2);
}

//�h���[
void CObjRock::Draw()
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