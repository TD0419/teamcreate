#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjTitle.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjTitle::Init()
{
	m_mode = 0;				//���[�h�I��ϐ��̏�����
	m_keypush_flag = true;	//�L�[�t���O�̏�����
	m_enter_key_flag = true;

	//�����̃O���t�B�b�N�쐬
	Font::SetStrTex(L"Start");	//�X�^�[�g
	Font::SetStrTex(L"Option");	//�I�v�V����
	Font::SetStrTex(L"Exit");	//�I��

	//�f�o�b�O�p
	Font::SetStrTex(L"��");	//��

	((UserData*)Save::GetData())->stagenum = 1;
}

//�A�N�V����
void CObjTitle::Action()
{
	//���L�[�������ꂽ��
	if (Input::GetVKey(VK_UP) == true)
	{
		//1�ȏ�@���@�L�[�t���O��true�@�Ȃ�
		if (m_mode >= 1 && m_keypush_flag == true)
		{
			m_mode--;	//���[�h�ԍ���1���炷
			m_keypush_flag = false;	//�L�[�t���O���I�t�ɂ���
		}
	}
	//���L�[�������ꂽ��
	else if (Input::GetVKey(VK_DOWN) == true)
	{
		//1�ȉ��@���@�L�[�t���O��true�@�Ȃ�
		if (m_mode <= 1 && m_keypush_flag == true)
		{
			m_mode++;	//���[�h�ԍ���1���₷
			m_keypush_flag = false;	//�L�[�t���O���I�t�ɂ���
		}
	}
	//���Ɓ���������ĂȂ��Ƃ�
	else
		m_keypush_flag = true;//�L�[�t���O���I���ɂ���

	if (Input::GetVKey(VK_RETURN) == false) //�@Enter�L�[��������ĂȂ������烁�C���Ɉڍs�ł���悤�ɂ���
	{
		m_enter_key_flag = false;
	}

	if (m_enter_key_flag == false) // �Q�[���I�[�o�[���炷���Ƀ��C���ɔ��ł��܂��̂Œ��������Ă����C���ɔ�΂���Ȃ��悤�ɂ����B
	{
		//�G���^�[�L�[�������ꂽ��
		if (Input::GetVKey(VK_RETURN) == true)
		{
			switch (m_mode)
			{
			case 0:
			{
				//�V�[�����C���Ɉړ�
				Scene::SetScene(new CSceneMain);
				break;
			}
			case 1:
			{
				//�I�v�V����
				break;
			}
			case 2:
			{
				//�Q�[���I��
				exit(0);
				break;
			}
			}
		}
	}
}

//�h���[
void CObjTitle::Draw()
{
	float color[4] = { 1.0f,1.0f,1.0f,1.0f };	//�`��̐F
	RECT_F src, dst;

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left+1024.0f;
	src.m_bottom = src.m_top+767.0f;

	//�`��ʒu
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = dst.m_left+1024.0f;
	dst.m_bottom = dst.m_top+767.0f;

	//�`��
	Draw::Draw(GRA_TITLE, &src, &dst, color, 0.0f);
	//���j���[�`��
	Font::StrDraw(L"Start"	, WINDOW_SIZE_W - 300.0f, WINDOW_SIZE_H/2.0f			, CHAR_SIZE, color);
	Font::StrDraw(L"Option"	, WINDOW_SIZE_W - 300.0f, WINDOW_SIZE_H/2.0f +  80.0f	, CHAR_SIZE, color);
	Font::StrDraw(L"Exit"	, WINDOW_SIZE_W - 300.0f, WINDOW_SIZE_H/2.0f + 160.0f	, CHAR_SIZE, color);


	//�f�o�b�O�p�Ɂ���\��
	Font::StrDraw(L"��"		, WINDOW_SIZE_W - 350.0f, WINDOW_SIZE_H / 2.0f + 80.0f * m_mode , CHAR_SIZE, color);

	
}