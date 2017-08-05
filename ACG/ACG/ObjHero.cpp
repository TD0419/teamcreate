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
	m_r = 0.0f;

}

//アクション
void CObjHero::Action()
{
	//左キーがおされたとき
	if (Input::GetVKey(VK_LEFT) == true)
	{
		m_vx -= 1.0f;
	}

	//右キーがおされたとき
	if (Input::GetVKey(VK_LEFT) == true)
	{
		m_vx += 1.0f;
	}

	//左キーがおされたとき
	if (Input::GetVKey(VK_LEFT) == true)
	{
		m_vx -= 1.0f;
	}

	//右キーがおされたとき
	if (Input::GetVKey(VK_RIGHT) == true)
	{
		m_vx += 1.0f;
	}
	
	//上キーがおされたとき
	if (Input::GetVKey(VK_UP) == true)
	{
		m_vx -= 1.0f;
	}

	//下キーがおされたとき
	if (Input::GetVKey(VK_DOWN) == true)
	{
		m_vx += 1.0f;
	}


	//移動ベクトルをポジションに加算
	m_px += m_vx * 3.0f;
	m_py += m_vy * 3.0f;

	//移動ベクトルを初期化
	m_vx = 0.0f;
	m_vy = 0.0f;

}

//ドロー
void CObjHero::Draw()
{
	//debug-------------
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//切り取り位置
	src.m_top		= 0.0f;
	src.m_left		= 0.0f;
	src.m_right		= 256.0f;
	src.m_bottom	= 256.0f;

	//描画位置
	dst.m_top		= 0.0f + m_py + m_scroll_y;
	dst.m_left		= 0.0f + m_px + m_scroll_x;
	dst.m_right		= dst.m_left + HERO_SIZE;
	dst.m_bottom	= dst.m_top + HERO_SIZE;

	Draw::Draw(0, &src, &dst, color, m_r);
}