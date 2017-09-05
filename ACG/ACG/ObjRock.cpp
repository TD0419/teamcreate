//�g�p����w�b�_�[�t�@�C���@
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjRock.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjRock::CObjRock(int x, int y)
{
	m_px = x * ROCK_SIZE;
	m_py = y * ROCK_SIZE;
}

//�C�j�V�����C�Y
void CObjRock::Init()
{
	//�����蔻��pHitBox���쐬                          
	Hits::SetHitBox(this, m_px, m_py, ROCK_SIZE, ROCK_SIZE, ELEMENT_GIMMICK, OBJ_ROCK, 1);
}

//�A�N�V����
void CObjRock::Action()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	
	//�e�ƐڐG���Ă��邩�ǂ����𒲂ׂ�@//ObjEnemy�Ɠ����悤�ɂ����ق������������m��Ȃ��B
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{
		this->SetStatus(false);		//���g�ɍ폜���߂��o��
		Hits::DeleteHitBox(this);	//�₪���L����HitBox�ɍ폜����
	}

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);

}

//�h���[
void CObjRock::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;
	
	//�`��ʒu
	dst.m_top = m_py - obj_m->GetScrollY();
	dst.m_left = m_px - obj_m->GetScrollX();
	dst.m_right = dst.m_left + ROCK_SIZE;
	dst.m_bottom = dst.m_top + ROCK_SIZE;

	//�`��
	Draw::Draw(10, &src, &dst, color, 0.0f);
}