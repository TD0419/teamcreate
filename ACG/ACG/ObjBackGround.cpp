#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjBackGround.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjBackGround::Init()
{
	 m_px=0.0f;	// 背景X座標
	 m_py=0.0f;	// 背景Y座標
}

//アクション
void CObjBackGround::Action()
{
}

//ドロー
void CObjBackGround::Draw()
{
	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left =0.0f;
	src.m_right =src.m_left + 1536.0f;
	src.m_bottom = src.m_top + 1536.0f;

	//描画位置
	dst.m_top =  WINDOW_SIZE_H - src.m_bottom - src.m_top - objmap->GetScrollY() + 15.0f;//少し調整用(+15)
	dst.m_left = 1536.0f - src.m_right - src.m_left;
	dst.m_right = 1536.0f;
	dst.m_bottom = WINDOW_SIZE_H - objmap->GetScrollY() + 900.0f;//調整用(＋900.0f)

	//描画
	Draw::Draw(GRA_BACKGROUND, &src, &dst, color, 0.0f);
	
}