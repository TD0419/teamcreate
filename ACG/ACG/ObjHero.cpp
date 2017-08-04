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
}

//�A�N�V����
void CObjHero::Action()
{
	m_px += m_vx;
	m_py += m_vy;
}

//�h���[
void CObjHero::Draw()
{
	//debug-------------
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };
	
	//debug-------------
	Font::StrDraw(L"A", m_px, m_py, 32.0f, color);
	//-----------------
}