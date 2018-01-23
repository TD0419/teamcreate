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
	m_px =(float)x * BLOCK_SIZE;
	m_py =(float)y * BLOCK_SIZE;
}

//イニシャライズ
void CObjSign::Init()
{
	//フラグ初期化
	m_strdrow = false;

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
	//ボタンの情報とる
	CObjButton* objbutton = (CObjButton*)Objs::GetObj(OBJ_BUTTON);

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
	//主人公オブジェクトを持ってくる
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);
	
	//枠線　&　文字　-------------------------------------------------------------

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY() -SIGN_SIZE * 6.0f ;
	dst.m_left = m_px - objmap->GetScrollX() - 122.0f;
	dst.m_right = dst.m_left + 300.0f;
	dst.m_bottom = dst.m_top + SIGN_SIZE * 4.0f;
	//-------------------------------------------------------------

	//文字を表示させるフラグオンの時
	if (m_strdrow == true)
	{
		
		//ステージ別の文字描画
		switch (((UserData*)Save::GetData())->stagenum)
		{
			case 1://ステージ1
			{
				//二個目の看板のテキスト
				if (m_map_x == 68 && m_map_y == 22)
				{
					//切り取り位置
					src.m_top = 257.0f;
					src.m_left = 0.0f;
					src.m_right = 297.0f;
					src.m_bottom = 386.0f;
					//描画
					Draw::Draw(GRA_SIGN_FRAME, &src, &dst, color, 0.0f);
				}
				else
				{
					//切り取り位置
					src.m_top = 0.0f;
					src.m_left = 0.0f;
					src.m_right = 297.0f;
					src.m_bottom = 128.0f;
					//描画
					Draw::Draw(GRA_SIGN_FRAME, &src, &dst, color, 0.0f);
				}
				break;
			}
			case 3://ステージ3
			{
				
				//二個目の看板のテキスト
				if (m_map_x == 50 && m_map_y == 17)
				{
					if (objhero->GetRopeAniCon()==false)
					{
						//切り取り位置
						src.m_top = 128.0f;
						src.m_left = 296.0f;
						src.m_right = 593.0f;
						src.m_bottom = 257.0f;
						//描画
						Draw::Draw(GRA_SIGN_FRAME, &src, &dst, color, 0.0f);
					}
				}
				else
				{
					//切り取り位置
					src.m_top = 128.0f;
					src.m_left = 0.0f;
					src.m_right = 297.0f;
					src.m_bottom = 257.0f;
					//描画
					Draw::Draw(GRA_SIGN_FRAME, &src, &dst, color, 0.0f);
				}
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