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
	m_button_x = x;
	m_button_y = y;
}

//�C�j�V�����C�Y
void CObjButton::Init()
{
	m_trick_flag = false;
}

//�A�N�V����
void CObjButton::Action()
{
	////�e�ƐڐG���Ă��邩�ǂ����𒲂ׂ�
	//if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	//{
	//	m_trick_flag = true; //�e�Ƃ������Ă���Ȃ�true������
	//}
}

//�h���[
void CObjButton::Draw()
{

}