#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjTime.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjTime::Init()
{
	//����(�t���[����)���O�ɐݒ�
	m_time = 0;

	m_px = 900;
	m_py = 20;
}

//�A�N�V����
void CObjTime::Action()
{
	//����(�t���[����)
	m_time++;

}

//�h���[
void CObjTime::Draw()
{
	//�F���@RGB
	float color[4] = {1.0f,1.0f,1.0f,1.0f};
	//���Ԃ�\�������镶����
	wchar_t str[256];

	//�b��10�����Ȃ�O��O�ɕt����
	if(m_time / 60 % 60 < 10)
		swprintf_s(str, L"%d:0%d", m_time / 60 / 60,m_time / 60 % 60);
	//���̂܂�
	else
		swprintf_s(str, L"%d:%d", m_time / 60 / 60, m_time / 60 % 60);
	//���Ԃ�\��
	Font::StrDraw(str, m_px, m_py, 50, color);
}