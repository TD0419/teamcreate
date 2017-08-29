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

}