#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameHead.h"
#include "ObjWireMesh.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjWireMesh::CObjWireMesh(float x, float y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjWireMesh::Init()
{
	//�����蔻��pHitBox���쐬                          
	Hits::SetHitBox(this, m_px, m_py, WIRE_MESH_SIZE_WIDTH, WIRE_MESH_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_WIRE_MESH, 1);
}

//�A�N�V����
void CObjWireMesh::Action()
{
	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//�h���[
void CObjWireMesh::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + 640.0f;
	src.m_bottom = src.m_top + 64.0f;

	//�`��ʒu
	dst.m_top =  m_py - objmap->GetScrollY() ;
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + WIRE_MESH_SIZE_WIDTH;
	dst.m_bottom = dst.m_top + WIRE_MESH_SIZE_HEIGHT;

	//�`��
	Draw::Draw(GRA_WIRE_MASH, &src, &dst, color, 0.0f);
	//-------------------------------------------------------
}