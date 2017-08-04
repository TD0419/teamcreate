#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

//debug------------------
#include "GameL\DrawFont.h"
//-------------------

#include "GameHead.h"
#include "ObjHero.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjHero::CObjHero()
{

}

//イニシャライズ
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

//アクション
void CObjHero::Action()
{
	m_Hero_x += m_Hero_vx;
	m_Hero_y += m_Hero_vy;
}

//ドロー
void CObjHero::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };
	
	//debug-------------
	Font::StrDraw(L"A", m_Hero_vx, m_Hero_vy, 32.0f, color);
	//-----------------
}