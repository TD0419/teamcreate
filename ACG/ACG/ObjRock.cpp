//�g�p����w�b�_�[�t�@�C���@
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjRock.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjRock::CObjRock(float x, float y)
{
	m_x = x;
	m_y = y;
}

//�C�j�V�����C�Y
void CObjRock::Init()
{
	//�����蔻��pHitBox���쐬                          ��
	Hits::SetHitBox(this, m_x, m_y, 128.0f, 198.0f, ELEMENT_NULL, OBJ_ROCK, 1);
}

//�A�N�V����
void CObjRock::Action()
{
	////�u���b�N���������Ă���
	//CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	////HitBox�̈ʒu�̕ύX
	//CHitBox* hit = Hits::GetHitBox(this);
	//hit->SetPos(m_x + block->GetScroll(), m_y);

	////�e�ƐڐG���Ă��邩�ǂ����𒲂ׂ�@//ObjEnemy�Ɠ����悤�ɂ����ق������������m��Ȃ��B
	//if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	//{
	//	this->SetStatus(false);		//���g�ɍ폜���߂��o��
	//	Hits::DeleteHitBox(this);	//�₪���L����HitBox�ɍ폜����
	//}
}

//�h���[
void CObjRock::Draw()
{

}