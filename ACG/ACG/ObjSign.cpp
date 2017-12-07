#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjSign.h"
#include "Function.h"
#include "GameL\UserData.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjSign::CObjSign(int x, int y)
{
	m_map_x = x;
	m_map_y = y;
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjSign::Init()
{
	//�t���O������
	m_strdrow = false;

	//�X�e�[�W�ʂ̕����ǂݍ���
	switch (((UserData*)Save::GetData())->stagenum)
	{
		case 1:
		{
			//�X�e�[�W1�̓�ڂ̊Ŕ̃e�L�X�g
			if (m_map_x == 68 && m_map_y == 22)
			{
				//�����Z�b�g
				Font::SetStrTex(L"�u��͏e�ŉ��邼�v");
			}
			else
			{
				Font::SetStrTex(L"�u��ň�������ƥ���v"); //��ڂ̊Ŕ̃e�L�X�g
			}
			break;
		}
		case 2://�X�e�[�W�Q
		{
			Font::SetStrTex(L"�����ɉ������邩��");
			break;
		}
	}

	//�����蔻��
	Hits::SetHitBox(this, m_px, m_py, SIGN_SIZE+32, SIGN_SIZE, ELEMENT_GIMMICK, OBJ_SIGN, 1);
}

//�A�N�V����
void CObjSign::Action()
{
	//��ʊO�Ȃ�
	if (WindowCheck(m_px, m_py, SIGN_SIZE, SIGN_SIZE) == false)
	{
		WindowOutDelete(this, m_map_x, m_map_y);//�폜����(��������)
		return;
	}

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
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f,1.0f};
	//�`��J���[(����)
	float color_str[4] = { 0.0f,0.0f,0.0f,1.0f};

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�g���@&�@�����@-------------------------------------------------------------
	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f ;
	src.m_right = 256.0f ;
	src.m_bottom = 256.0f;

	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY() -SIGN_SIZE * 6.0f ;
	dst.m_left = m_px - objmap->GetScrollX() - 122.0f;
	dst.m_right = dst.m_left + 300.0f;
	dst.m_bottom = dst.m_top + SIGN_SIZE * 4.0f;
	//-------------------------------------------------------------

	//��l���Ɠ������Ă��鎞
	if (m_strdrow == true)
	{
		//�`��
		Draw::Draw(GRA_SIGN_FRAME, &src, &dst, color, 0);

		//�X�e�[�W�ʂ̕����`��
		switch (((UserData*)Save::GetData())->stagenum)
		{
			case 1://�X�e�[�W1
			{
				//��ڂ̊Ŕ̃e�L�X�g
				if (m_map_x == 68 && m_map_y == 22)
				{
					//�����Z�b�g
					Font::StrDraw(L"��͏e�ŉ��邼", dst.m_left + 15.0f, dst.m_top + 48.0f, 32.0f, color_str);
				}
				else
				{
					Font::StrDraw(L"��ň�������ƥ��", dst.m_left + 15.0f, dst.m_top + 48.0f, 32.0f, color_str); //��ڂ̊Ŕ̃e�L�X�g
				}
				break;
			}
			case 2://�X�e�[�W2
			{
				//�����Z�b�g
				Font::StrDraw(L"�����ɉ������邩��", dst.m_left + 7.0f, dst.m_top + 48.0f, 32.0f, color_str);
				break;
			}
		}
	}
	//----------------------------------------------------------------------------

	//�Ŕ{��--------------------------------------------------------------
	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//�`��̈ʒu
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + 64.0f;
	dst.m_bottom = dst.m_top + 64.0f;

	//�`��
	Draw::Draw(GRA_SIGN, &src, &dst, color, 0.0f);
	//�Ŕ{��--------------------------------------------------------------
}