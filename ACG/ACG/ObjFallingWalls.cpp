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
	////�`��J���[
	//float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	//RECT_F src, dst;

	////�}�b�v�I�u�W�F�N�g�������Ă���
	//CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	////�؂���ʒu
	//src.m_top = 0.0f;
	//src.m_left = 0.0f;
	//src.m_right = 64.0f;
	//src.m_bottom = 64.0f;

	////�`��ʒu
	//dst.m_top = m_py - objmap->GetScrollY();
	//dst.m_left = m_px - objmap->GetScrollX();
	//dst.m_right = dst.m_left + FALLING_WALLS_SAIZE;
	//dst.m_bottom = dst.m_top + FALLING_WALLS_SAIZE;

	////�`��
	//Draw::Draw(, &src, &dst, color, 0.0f);
}