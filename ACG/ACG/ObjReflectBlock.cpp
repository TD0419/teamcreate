#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjReflectBlock.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjReflectBlock::CObjReflectBlock(int x, int y)
{
	m_x = x * BLOCK_SIZE;
	m_y = y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjReflectBlock::Init()
{
	//�����蔻��
	Hits::SetHitBox(this, m_x, m_y, BLOCK_SIZE, BLOCK_SIZE, ELEMENT_BLOCK, OBJ_REFLECT_BLOCK, 1);
}

//�A�N�V����
void CObjReflectBlock::Action()
{
	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_x, m_y);
}

//�h���[
void CObjReflectBlock::Draw()
{


}