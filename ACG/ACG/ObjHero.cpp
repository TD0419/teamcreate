#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

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
	m_px = 0.0f;
	m_py = 0.0f;
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_scroll_x = 0.0f;
	m_scroll_y = 0.0f;
}

//アクション
void CObjHero::Action()
{
	//左キーが押された時
	if (Input::GetVKey(VK_LEFT) == true)
	{
		m_vx = -1.0f;
	}

	//右キーが押された時
	if (Input::GetVKey(VK_RIGHT) == true)
	{
		m_vx = 1.0f;
	}

	//上キーが押された時
	if (Input::GetVKey(VK_UP) == true)
	{
		m_vy = -1.0f;
	}

	//下キーが押された時
	if (Input::GetVKey(VK_DOWN) == true)
	{
		m_vy = 1.0f;
	}

	//移動ベクトルをポジションに合成
	m_px += m_vx;
	m_py += m_vy;

	//移動ベクトルの初期化
	m_vx = 0.0f;
	m_vy = 0.0f;

	//debug------------------------------
	wchar_t str[256];
	swprintf_s(str, L"m_px %d m_py %d \n",m_px,m_py);

	OutputDebugStringW(str);
	//--------------------------------

}

//ドロー
void CObjHero::Draw()
{
	//debug-------------
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };
	
	RECT_F src;
	RECT_F dst;

	src.m_top		= 0.0f;
	src.m_left		= 0.0f;
	src.m_right		= 512.0f;
	src.m_bottom	= 512.0f;

	dst.m_top		= 0.0f + m_py + m_scroll_y;
	dst.m_left		= 0.0f + m_px + m_scroll_x;
	dst.m_right		= dst.m_left + HERO_SIZE;
	dst.m_bottom	= dst.m_top + HERO_SIZE;

	Draw::Draw(0, &src, &dst, color, 0.0f);
	//-----------------
}