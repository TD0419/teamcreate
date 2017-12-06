//�g�p����w�b�_�[�t�@�C���@
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjFallingWalls.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjFallingWalls::CObjFallingWalls(int x, int y)
{
	m_px = (float)x * FALLING_WALLS_SAIZE;
	m_py = (float)y * FALLING_WALLS_SAIZE;
}

//�C�j�V�����C�Y
void CObjFallingWalls::Init()
{
	//�����蔻��pHitBox���쐬                          
	Hits::SetHitBox(this, m_px, m_py, FALLING_WALLS_SAIZE, FALLING_WALLS_SAIZE, ELEMENT_GIMMICK, OBJ_FALLING_WALLS, 1);
}

//�A�N�V����
void CObjFallingWalls::Action()
{
	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//�h���[
void CObjFallingWalls::Draw()
{
	
}