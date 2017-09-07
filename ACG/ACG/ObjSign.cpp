#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjSign.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjSign::CObjSign(int x, int y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//イニシャライズ
void CObjSign::Init()
{
	//フラグ初期化
	m_strdrow = false;

	//文字セット
	Font::SetStrTex(L"ガノンドロフΩ");

	//当たり判定
	Hits::SetHitBox(this, m_px, m_py, SIGN_SIZE, SIGN_SIZE, ELEMENT_GIMMICK, OBJ_SIGN, 1);
}

//アクション
void CObjSign::Action()
{
	//当たり判定をもってくる
	CHitBox* hit = Hits::GetHitBox(this);

	//主人公とあたっていれば
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		m_strdrow = true;//フラグをオンにする
	}
	else
	{
		m_strdrow = false;//フラグをオフにする
	}

	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//ドロー
void CObjSign::Draw()
{
	//色
	float c[4] = {1.0f,1.0f,1.0f,1.0f};

	//主人公と当たっている時
	if (m_strdrow == true)
	{
		Font::StrDraw(L"ガノンドロフΩ", m_px, m_py - SIGN_SIZE, 32.0f, c);
	}
}