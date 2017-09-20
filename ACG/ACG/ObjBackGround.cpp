#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjBackGround.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjBackGround::CObjBackGround()
{

}

//イニシャライズ
void CObjBackGround::Init()
{
	 m_x=0;	// 背景X座標
	 m_y=0;	// 背景Y座標
}

//アクション
void CObjBackGround::Action()
{
	
}

//ドロー
void CObjBackGround::Draw()
{
	//マップオブジェクトを持ってくる
	CObjMap* map = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left =0.0f;
	src.m_right =src.m_left + 1536;
	src.m_bottom = src.m_top + 1536;

	//描画位置
	dst.m_top =  WINDOW_SIZE_H - src.m_bottom - src.m_top - map->GetScrollY() + 15;//少し調整用(+15)
	dst.m_left = 1536 - src.m_right - src.m_left;
	dst.m_right = 1536;
	dst.m_bottom = WINDOW_SIZE_H - map->GetScrollY() + 15;//少し調整用(＋15)

	//描画
	Draw::Draw(15, &src, &dst, color, 0.0f);
	
}