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
	m_time = 0;

	////�l�����p
	//int w;

	////�X�R�A�������L���O�̍Ō�ɓ����
	//((UserData*)Save::GetData())->m_ranking[RANKING_MAX_COUNT - 1] = ((UserData*)Save::GetData())->m_point;

	////�����L���O�ϓ��m�F
	////�o�u���\�[�g
	//for (int i = 0; i < RANKING_MAX_COUNT - 1; i++)
	//{
	//	for (int j = i + 1; j < RANKING_MAX_COUNT; j++)
	//	{
	//		if (((UserData*)Save::GetData())->m_ranking[i] < ((UserData*)Save::GetData())->m_ranking[j])
	//		{
	//			//�l�̕ύX
	//			w = ((UserData*)Save::GetData())->m_ranking[i];
	//			((UserData*)Save::GetData())->m_ranking[i] = ((UserData*)Save::GetData())->m_ranking[j];
	//			((UserData*)Save::GetData())->m_ranking[j] = w;
	//		}
	//	}
	//}

	////�X�e�[�W1�ŏ���������
	//((UserData*)Save::GetData())->m_stage_count = 1;

	//�Z�[�u
	Save::Seve();
}

//�A�N�V����
void CObjGameOver::Action()
{
	m_time++;

	//if (m_time > 400)
	//{
	//	//A����������A���j���[��ʂ�
	//	if (Input::GetVKey('Q') == true)
	//	{
	//		if (m_key_flag == true)
	//		{
	//			//�����L���O�ɔ��f�����X�R�A������������
	//			((UserData*)Save::GetData())->m_point = 0;
	//		}
	//	}
	//	else
	//	{
	//		m_key_flag = true;
	//		Scene::SetScene(new CSceneMenu());//���j���[��ʂ�
	//		
	//	}
	//}
}

//�h���[
void CObjGameOver::Draw()
{
	//float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	//RECT_F src;	//�`���؂���ʒu
	//RECT_F dst;	//�`���\���ʒu

	//			//�w�i--------------------------------
	//			//�؂���ʒu�ݒ�
	//src.m_top = 0.0f;
	//src.m_left = 0.0f;
	//src.m_right = 512.0f;
	//src.m_bottom = 512.0f;

	////�\���ʒu�ݒ�
	//dst.m_top = 0.0f;
	//dst.m_left = 0.0f;
	//dst.m_right = 800.0f;
	//dst.m_bottom = 600.0f;

	////�`��
	//Draw::Draw(7, &src, &dst, c, 0.0f);
}