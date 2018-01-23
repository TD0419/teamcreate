#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjGameOver.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjGameOver::Init()
{
	m_mode = 0;				//���[�h�I��ϐ��̏�����
	m_keypush_flag = true;	//�L�[�t���O�̏�����
	m_enter_key_flag = true;
	

	//�����̃O���t�B�b�N�쐬
	Font::SetStrTex(L"GAME OVER");
	Font::SetStrTex(L"Title");
	Font::SetStrTex(L"Continue");
	Audio::Start(GAMEOVER);	//BGM���Ȃ炷


}

//�A�N�V����
void CObjGameOver::Action()
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
		if (m_mode <= 1 && m_keypush_flag == true)
		{
			m_mode+=1;	//���[�h�ԍ���1���₷
			m_keypush_flag = false;	//�L�[�t���O���I�t�ɂ���
			
		}
	}
	//W�AS�A���A����������ĂȂ��Ƃ�
	else
		m_keypush_flag = true;//�L�[�t���O���I���ɂ���

	if (Input::GetVKey(VK_RETURN) == false)
	{
		m_enter_key_flag = false;
	}

	if (m_enter_key_flag == false) //���������Ă��e��V�[���ɂ����ړ��ł��Ȃ��悤�ɂ��鏈���B
	{
		//�G���^�[�L�[�������ꂽ��
		if (Input::GetVKey(VK_RETURN) == true)
		{
			switch (m_mode)
			{
				case 0:	//Continue
				{
					Scene::SetScene(new CSceneMain(+3));
					break;
				}
				case 1:	//Restart
				{
					((UserData*)Save::GetData())->stagenum = 1;
					Scene::SetScene(new CSceneMain());
					break;
				}
				case 2:	//Title
				{
					Scene::SetScene(new CSceneTitle());
					break;
				}
			}
		}
	}
}

//�h���[
void CObjGameOver::Draw()
{
	float color_white[4] = { 1.0f,1.0f,1.0f,1.0f }; //���F�A��{�F
	float color_yellow[4] = { 1.0f,1.0f,0.0f,1.0f };//���F

	RECT_F src;	//�`���؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�؂���ʒu�ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	////�\���ʒu�ݒ�
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1024.0f;
	dst.m_bottom =1024.0f;

	//�`��
	Draw::Draw(GRA_GAME_OVER, &src, &dst, color_white, 0.0f);
	//�����`��
	wchar_t str[3][12] =
	{
		L"Continue",
		L"Restart",
		L"Title",
	};

	for (int i = 0; i < 3; i++)
	{
		if( i == m_mode )//�I�����Ă��郂�[�h�̂݉��F�ŕ\������
			Font::StrDraw(str[i], WINDOW_SIZE_W - 250.0f, WINDOW_SIZE_H - 300.0f + i*(FONT_SIZE_GO * 1.5f), FONT_SIZE_GO + 10.0f, color_yellow);
		else
			Font::StrDraw(str[i], WINDOW_SIZE_W - 250.0f, WINDOW_SIZE_H - 300.0f + i*(FONT_SIZE_GO * 1.5f), FONT_SIZE_GO, color_white);
	}
}