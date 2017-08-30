#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjLift.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjLift::CObjLift(int x, int y)
{
	m_px = x * LIFT_SIZE;
	m_py = y * LIFT_SIZE;
}

//�C�j�V�����C�Y
void CObjLift::Init()
{
	//�����蔻��
	Hits::SetHitBox(this, m_px, m_py, LIFT_SIZE, LIFT_SIZE, ELEMENT_GIMMICK, OBJ_LIFT, 1);

}

//�A�N�V����
void CObjLift::Action()
{
	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//�h���[
void CObjLift::Draw()
{
}