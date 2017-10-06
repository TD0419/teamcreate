//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjButton.h"
#include "Function.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjButton::CObjButton(int x, int y)
{
	m_px = x;
	m_py = y;
}

//�C�j�V�����C�Y
void CObjButton::Init()
{
	m_trick_flag = false;

	//�����蔻��
	Hits::SetHitBox(this, m_px, m_py, BUTTON_SIZE, BUTTON_SIZE, ELEMENT_GIMMICK, OBJ_BUTTON, 1);

}

//�A�N�V����
void CObjButton::Action()
{
	
	////�e�ƐڐG���Ă��邩�ǂ����𒲂ׂ�
	//if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	//{
	//	m_trick_flag = true; //�e�Ƃ������Ă���Ȃ�true������
	//}

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);

}

//�h���[
void CObjButton::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = BUTTON_SIZE;
	src.m_bottom = BUTTON_SIZE;

	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + BUTTON_SIZE;
	dst.m_bottom = dst.m_top + BUTTON_SIZE;

	//�`��
	Draw::Draw(20, &src, &dst, color, 0.0f);
}