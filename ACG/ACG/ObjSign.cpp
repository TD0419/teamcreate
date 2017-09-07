#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjSign.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjSign::CObjSign(int x, int y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjSign::Init()
{
	//�t���O������
	m_strdrow = false;

	//�����Z�b�g
	Font::SetStrTex(L"�K�m���h���t��");

	//�����蔻��
	Hits::SetHitBox(this, m_px, m_py, SIGN_SIZE, SIGN_SIZE, ELEMENT_GIMMICK, OBJ_SIGN, 1);
}

//�A�N�V����
void CObjSign::Action()
{
	//�����蔻��������Ă���
	CHitBox* hit = Hits::GetHitBox(this);

	//��l���Ƃ������Ă����
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		m_strdrow = true;//�t���O���I���ɂ���
	}
	else
	{
		m_strdrow = false;//�t���O���I�t�ɂ���
	}

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//�h���[
void CObjSign::Draw()
{
	//�F
	float c[4] = {1.0f,1.0f,1.0f,1.0f};

	//��l���Ɠ������Ă��鎞
	if (m_strdrow == true)
	{
		Font::StrDraw(L"�K�m���h���t��", m_px, m_py - SIGN_SIZE, 32.0f, c);
	}
}