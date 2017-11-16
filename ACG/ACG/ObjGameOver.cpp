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
	m_key_flag = false;
	m_audio_se = 0;//SE�̉��y�̊Ǘ�
	//�����̃O���t�B�b�N�쐬
	Font::SetStrTex(L"GAMEOVER");	//
}

//�A�N�V����
void CObjGameOver::Action()
{
	
}

//�h���[
void CObjGameOver::Draw()
{
	float color[4] = { 1.0f,1.0f,1.0f,1.0f };

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
	Draw::Draw(GRA_GAME_OVER, &src, &dst, color, 0.0f);
	//���j���[�`��
	Font::StrDraw(L"GAMEOVER", 2.f, WINDOW_SIZE_H / 3.f, 45.0f, color);
}