//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "ObjGameClear.h"
#include "GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjGameClear::Init()
{

}

//�A�N�V����
void CObjGameClear::Action()
{

}

//�h���[
void CObjGameClear::Draw()
{
	//�^�C�g�����
	float color[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//�`���؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	//�`��ʒu
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//�w�i�`��
	Draw::Draw(1, &src, &dst, color, 0.0f);

}