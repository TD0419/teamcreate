//�g�p����w�b�_�[�t�@�C���@
#include "GameL\HitBoxManager.h"
#include "GameHead.h"
#include "ObjWater.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjWater::CObjWater(int x, int y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjWater::Init()
{
	//�����蔻��
	Hits::SetHitBox(this, m_px, m_py, WATER_SIZE, WATER_SIZE, ELEMENT_GIMMICK, OBJ_WATER, 1);
}

//�A�N�V����
void CObjWater::Action()
{
	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//�h���[
void CObjWater::Draw()
{
}