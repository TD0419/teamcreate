#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjRopeSwitch.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjRopeSwitch::CObjRopeSwitch(int x, int y)
{
	m_px = x * ROPE_SWITCH_SIZE;
	m_py = y * ROPE_SWITCH_SIZE;

}

//�C�j�V�����C�Y
void CObjRopeSwitch::Init()
{

	//�����蔻��
	Hits::SetHitBox(this, m_px, m_py, ROPE_SWITCH_SIZE, ROPE_SWITCH_SIZE, ELEMENT_GIMMICK, OBJ_ROPE_SWITCH, 1);

}

//�A�N�V����
void CObjRopeSwitch::Action()
{

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);

}

//�h���[
void CObjRopeSwitch::Draw()
{

}