#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjLadders.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjLadders::CObjLadders(int x, int y)
{
	m_px = x * LADDERS_SIZE;
	m_py = y * LADDERS_SIZE;
}

//�C�j�V�����C�Y
void CObjLadders::Init()
{
	//�����蔻��
	Hits::SetHitBox(this, m_px, m_py, LADDERS_SIZE, LADDERS_SIZE, ELEMENT_GIMMICK, OBJ_LADDERS, 1);
}

//�A�N�V����
void CObjLadders::Action()
{

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);

}

//�h���[
void CObjLadders::Draw()
{

}