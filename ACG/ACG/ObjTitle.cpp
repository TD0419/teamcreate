#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"
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
	Font::SetStrTex(L"Exit");	//�I��

	//�X�e�[�W1����X�^�[�g������
	((UserData*)Save::GetData())->stagenum = 1;

	Audio::Start(TITLE);
}

//�A�N�V����
void CObjTitle::Action()
{
	
	//W�L�[�@���́@���L�[�������ꂽ��
	if (Input::GetVKey('W') == true || Input::GetVKey(VK_UP) == true)
	{
		//1�ȏ�@���@�L�[�t���O��true�@�Ȃ�
		if (m_mode >= 1 && m_keypush_flag == true)
		{
			m_mode-=1;	//���[�h�ԍ���1���炷
			m_keypush_flag = false;	//�L�[�t���O���I�t�ɂ���	
		}
	}
	//S�L�[�@���́@���L�[�������ꂽ��
	else if (Input::GetVKey('S') == true || Input::GetVKey(VK_DOWN) == true)
	{
		//1�ȉ��@���@�L�[�t���O��true�@�Ȃ�
		if (m_mode <= 0 && m_keypush_flag == true)
		{
			m_mode+=1;	//���[�h�ԍ���1���₷
			m_keypush_flag = false;	//�L�[�t���O���I�t�ɂ���
			
		}
	}
	//W�AS�A���A����������ĂȂ��Ƃ�
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
	
	float color_white[4] = { 1.0f,1.0f,1.0f,1.0f }; //���F�A��{�F
	float color_yellow[4] = { 1.0f,1.0f,0.0f,1.0f };//���F
	RECT_F src, dst;

	//�؂���ʒu
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = src.m_left + 1024.0f;
	src.m_bottom = src.m_top  +  767.0f;

	//�`��ʒu
	dst.m_top    = 0.0f;
	dst.m_left   = 0.0f;
	dst.m_right  = dst.m_left + 1024.0f;
	dst.m_bottom = dst.m_top + 767.0f;

	//�`��
	Draw::Draw(GRA_TITLE, &src, &dst, color_white, 0.0f);

	//���j���[�`��
	//����Start���w���Ă���ꍇ�́AStart�̕��������F�ɂ���BExit�̕����͔��F�B
	if( m_mode == 0 )
	{
		Font::StrDraw(L"Start"	, WINDOW_SIZE_W - 250.0f, WINDOW_SIZE_H/2.0f + 40.0f    , FONT_SIZE_TITLE, color_yellow);
		Font::StrDraw(L"Exit"	, WINDOW_SIZE_W - 250.0f, WINDOW_SIZE_H/2.0f + 118.0f	, FONT_SIZE_TITLE - 10.0f, color_white);

	}
	
	//����Exit���w���Ă���ꍇ�́AExit�̕��������F�ɂ���BStart�̕����͔��F�B
	else if ( m_mode == 1 )
	{
		Font::StrDraw(L"Start", WINDOW_SIZE_W - 250.0f, WINDOW_SIZE_H / 2.0f + 40.0f, FONT_SIZE_TITLE -10.0f, color_white);
		Font::StrDraw(L"Exit", WINDOW_SIZE_W - 250.0f, WINDOW_SIZE_H / 2.0f + 118.0f, FONT_SIZE_TITLE, color_yellow);
	}
}