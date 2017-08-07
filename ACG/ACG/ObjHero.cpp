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
	m_px = WINDOW_SIZE_W/2.0f;
	m_py = WINDOW_SIZE_H / 2.0f;
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_r = 0.0f;

}

//アクション
void CObjHero::Action()
{
	//移動ーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	//左キーがおされたとき
	if (Input::GetVKey(VK_LEFT) == true)
	{
		m_vx -= 3.0f;
	}

	//右キーがおされたとき
	if (Input::GetVKey(VK_RIGHT) == true)
	{
		m_vx += 3.0f;
	}
	
	//上キーがおされたとき
	if (Input::GetVKey(VK_UP) == true)
	{
		m_vy -= 3.0f;
	}

	//下キーがおされたとき
	if (Input::GetVKey(VK_DOWN) == true)
	{
		m_vy += 3.0f;
	}
	
	Scroll();	//スクロール処理をおこなう

	//移動ベクトルをポジションに加算
	m_px += m_vx;
	m_py += m_vy;

	//移動ベクトルを初期化
	m_vx = 0.0f;
	m_vy = 0.0f;

	//移動終わり-----------------------------------------
}

//スクロール処理の関数
void CObjHero::Scroll()
{
	//マップオブジェクトを持ってくる
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//主人公が左または右のスクロールラインを超えそうなら
	if ((m_px + m_vx) < SCROLL_LINE_LEFT || (m_px + m_vx) > SCROLL_LINE_RIGHT)
	{
		obj_m->SetScrollX(m_vx);	//移動量をスクロールにセット
	}

	//主人公が上または下のスクロールラインを超えそうなら
	if ((m_py + m_vy) < SCROLL_LINE_UP || (m_py + m_vy) > SCROLL_LINE_DOWN) 
	{
		obj_m->SetScrollY(m_vy);	//移動量をスクロールにセット
	}

}

//ドロー
void CObjHero::Draw()
{
	
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top		= 0.0f;
	src.m_left		= 0.0f;
	src.m_right		= 512.0f;
	src.m_bottom	= 512.0f;

	//描画位置
	dst.m_top		= 0.0f + m_py - obj_m->GetScrollY();
	dst.m_left		= 0.0f + m_px - obj_m->GetScrollX();
	dst.m_right		= dst.m_left + HERO_SIZE;
	dst.m_bottom	= dst.m_top + HERO_SIZE;

	Draw::Draw(0, &src, &dst, color, m_r);
}