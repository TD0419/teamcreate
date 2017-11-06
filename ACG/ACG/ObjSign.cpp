#include "GameL\DrawTexture.h"
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
	Font::SetStrTex(L"???「ロープを使うのだよ諸君！」");

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
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f,1.0f};
	//描画カラー(文字)
	float color_str[4] = { 0.0f,0.0f,0.0f,1.0f};

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//枠線　&　文字　-------------------------------------------------------------
	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f ;
	src.m_right = 256.0f ;
	src.m_bottom = 256.0f;

	//描画位置
	dst.m_top = -SIGN_SIZE * 6.0f - 16.0f + m_py - objmap->GetScrollY();
	dst.m_left = -192.0f +SIGN_SIZE / 2.0f + m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + 384.0f;
	dst.m_bottom = dst.m_top + 128.0f;

	//主人公と当たっている時
	if (m_strdrow == true)
	{
		//描画
		Draw::Draw(GRA_SIGN_FRAME, &src, &dst, color, 0);
		Font::StrDraw(L"???「ロープを使うのだよ諸君！」", dst.m_left, dst.m_top + 32.0f , 32.0f, color_str);
	}
	//----------------------------------------------------------------------------

	//看板本体--------------------------------------------------------------
	//切り取り位置
	/*src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;
*/
	//描画の位置
	/*dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + LIFT_SIGN_WIDTH;
	dst.m_bottom = dst.m_top + LIFT_SIGN_HEIGHT;
*/
	//描画
//	Draw::Draw(GRA_SIGN_MAIN, &src, &dst, color, 0.0f);
	//看板本体--------------------------------------------------------------
}