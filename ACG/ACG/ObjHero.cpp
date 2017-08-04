#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

//debug------------------
#include "GameL\DrawFont.h"
//-------------------

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
	m_Hero_x = 0.0f;
	m_Hero_y = 0.0f;
	m_Hero_vx = 0.0f;
	m_Hero_vy = 0.0f;

	//debug---------------
	Font::SetStrTex(L"A");
	//-------------------

}

//�A�N�V����
void CObjHero::Action()
{
	m_Hero_x += m_Hero_vx;
	m_Hero_y += m_Hero_vy;
}

//�h���[
void CObjHero::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };
	
	//debug-------------
	Font::StrDraw(L"A", m_Hero_vx, m_Hero_vy, 32.0f, color);
	//-----------------
}