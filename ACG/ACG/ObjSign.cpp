#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjSign.h"
#include "Function.h"
#include "GameL\UserData.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjSign::CObjSign(int x, int y)
{
	m_map_x = x;
	m_map_y = y;
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//イニシャライズ
void CObjSign::Init()
{
	//フラグ初期化
	m_strdrow = false;

	//ステージ別の文字読み込み
	switch (((UserData*)Save::GetData())->stagenum)
	{
		case 1:
		{
			//ステージ1の二個目の看板のテキスト
			if (m_map_x == 68 && m_map_y == 22)
			{
				//文字セット
				Font::SetStrTex(L"「岩は銃で壊れるぞ」");
			}
			else
			{
				Font::SetStrTex(L"「縄で引っ張ると･･･」"); //一個目の看板のテキスト
			}
			break;
		}
		case 2://ステージ２
		{
			Font::SetStrTex(L"ここに何かあるかも");
			break;
		}
	}

	//当たり判定
	Hits::SetHitBox(this, m_px, m_py, SIGN_SIZE+32, SIGN_SIZE, ELEMENT_GIMMICK, OBJ_SIGN, 1);
}

//アクション
void CObjSign::Action()
{
	//画面外なら
	if (WindowCheck(m_px, m_py, SIGN_SIZE, SIGN_SIZE) == false)
	{
		WindowOutDelete(this, m_map_x, m_map_y);//削除処理(復活あり)
		return;
	}

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
	dst.m_top = m_py - objmap->GetScrollY() -SIGN_SIZE * 6.0f ;
	dst.m_left = m_px - objmap->GetScrollX() - 122.0f;
	dst.m_right = dst.m_left + 300.0f;
	dst.m_bottom = dst.m_top + SIGN_SIZE * 4.0f;
	//-------------------------------------------------------------

	//主人公と当たっている時
	if (m_strdrow == true)
	{
		//描画
		Draw::Draw(GRA_SIGN_FRAME, &src, &dst, color, 0);

		//ステージ別の文字描画
		switch (((UserData*)Save::GetData())->stagenum)
		{
			case 1://ステージ1
			{
				//二個目の看板のテキスト
				if (m_map_x == 68 && m_map_y == 22)
				{
					//文字セット
					Font::StrDraw(L"岩は銃で壊れるぞ", dst.m_left + 15.0f, dst.m_top + 48.0f, 32.0f, color_str);
				}
				else
				{
					Font::StrDraw(L"縄で引っ張ると･･･", dst.m_left + 15.0f, dst.m_top + 48.0f, 32.0f, color_str); //一個目の看板のテキスト
				}
				break;
			}
			case 2://ステージ2
			{
				//文字セット
				Font::StrDraw(L"ここに何かあるかも", dst.m_left + 7.0f, dst.m_top + 48.0f, 32.0f, color_str);
				break;
			}
		}
	}
	//----------------------------------------------------------------------------

	//看板本体--------------------------------------------------------------
	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//描画の位置
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + 64.0f;
	dst.m_bottom = dst.m_top + 64.0f;

	//描画
	Draw::Draw(GRA_SIGN, &src, &dst, color, 0.0f);
	//看板本体--------------------------------------------------------------
}