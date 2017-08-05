#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjHero.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjHero::CObjHero()
{

}

//�C�j�V�����C�Y
void CObjHero::Init()
{
	m_px = 0.0f;
	m_py = 0.0f;
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_scroll_x = 0.0f;
	m_scroll_y = 0.0f;
	m_r = 0.0f;

}

//�A�N�V����
void CObjHero::Action()
{
	//���L�[�������ꂽ�Ƃ�
	if (Input::GetVKey(VK_LEFT) == true)
	{
		m_vx -= 1.0f;
	}

	//�E�L�[�������ꂽ�Ƃ�
	if (Input::GetVKey(VK_LEFT) == true)
	{
		m_vx += 1.0f;
	}

	//���L�[�������ꂽ�Ƃ�
	if (Input::GetVKey(VK_LEFT) == true)
	{
		m_vx -= 1.0f;
	}

	//�E�L�[�������ꂽ�Ƃ�
	if (Input::GetVKey(VK_RIGHT) == true)
	{
		m_vx += 1.0f;
	}
	
	//��L�[�������ꂽ�Ƃ�
	if (Input::GetVKey(VK_UP) == true)
	{
		m_vx -= 1.0f;
	}

	//���L�[�������ꂽ�Ƃ�
	if (Input::GetVKey(VK_DOWN) == true)
	{
		m_vx += 1.0f;
	}


	//�ړ��x�N�g�����|�W�V�����ɉ��Z
	m_px += m_vx * 3.0f;
	m_py += m_vy * 3.0f;

	//�ړ��x�N�g����������
	m_vx = 0.0f;
	m_vy = 0.0f;

}

//�h���[
void CObjHero::Draw()
{
	//debug-------------
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�؂���ʒu
	src.m_top		= 0.0f;
	src.m_left		= 0.0f;
	src.m_right		= 256.0f;
	src.m_bottom	= 256.0f;

	//�`��ʒu
	dst.m_top		= 0.0f + m_py + m_scroll_y;
	dst.m_left		= 0.0f + m_px + m_scroll_x;
	dst.m_right		= dst.m_left + HERO_SIZE;
	dst.m_bottom	= dst.m_top + HERO_SIZE;

	Draw::Draw(0, &src, &dst, color, m_r);
}