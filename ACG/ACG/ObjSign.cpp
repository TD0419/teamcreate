#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjSign.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjSign::CObjSign(int x, int y)
{
	m_px = x;
	m_py = y;
}

//�C�j�V�����C�Y
void CObjSign::Init()
{
	
	//�����蔻��
	Hits::SetHitBox(this, m_px, m_py, SIGN_SIZE, SIGN_SIZE, ELEMENT_GIMMICK, OBJ_SIGN, 1);
}

//�A�N�V����
void CObjSign::Action()
{
	//���g��HitBox�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	//��l���Ƃ������Ă����
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		wchar_t* str
	}
}

//�h���[
void CObjSign::Draw()
{
}