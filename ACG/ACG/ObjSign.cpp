#include "GameL\DrawTexture.h"
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
	Font::SetStrTex(L"�w�r���Ȃ��u���m�ɂ̓w�r���Ȃ�����v");

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
	//�`��J���[�i�g�j
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };
	//�`��J���[(����)
	float c[4] = { 0.0f,0.0f,0.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* map = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f ;
	src.m_right = 256.0f ;
	src.m_bottom = 256.0f;

	//�`��ʒu
	dst.m_top = -SIGN_SIZE * 6.0f - 16.0f + m_py - map->GetScrollY();
	dst.m_left = -192.0f +SIGN_SIZE / 2.0f + m_px - map->GetScrollX();
	dst.m_right = dst.m_left + 384.0f;
	dst.m_bottom = dst.m_top + 128.0f;

	//��l���Ɠ������Ă��鎞
	if (m_strdrow == true)
	{
		//�`��
		Draw::Draw(17, &src, &dst, color, 0);
		Font::StrDraw(L"�w�r���Ȃ��u���m�ɂ̓w�r���Ȃ�����v", dst.m_left, dst.m_top + 32.0f , 32.0f, c);
	}
	
}