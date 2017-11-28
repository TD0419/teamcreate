//使用するヘッダーファイル　
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjFallingWalls.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjFallingWalls::CObjFallingWalls(int x, int y)
{
	m_px = (float)x * FALLING_WALLS_SAIZE;
	m_py = (float)y * FALLING_WALLS_SAIZE;
}

//イニシャライズ
void CObjFallingWalls::Init()
{
	//当たり判定用HitBoxを作成                          
	Hits::SetHitBox(this, m_px, m_py, FALLING_WALLS_SAIZE, FALLING_WALLS_SAIZE, ELEMENT_GIMMICK, OBJ_FALLING_WALLS, 1);
}

//アクション
void CObjFallingWalls::Action()
{
	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//ドロー
void CObjFallingWalls::Draw()
{
	////描画カラー
	//float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	//RECT_F src, dst;

	////マップオブジェクトを持ってくる
	//CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	////切り取り位置
	//src.m_top = 0.0f;
	//src.m_left = 0.0f;
	//src.m_right = 64.0f;
	//src.m_bottom = 64.0f;

	////描画位置
	//dst.m_top = m_py - objmap->GetScrollY();
	//dst.m_left = m_px - objmap->GetScrollX();
	//dst.m_right = dst.m_left + FALLING_WALLS_SAIZE;
	//dst.m_bottom = dst.m_top + FALLING_WALLS_SAIZE;

	////描画
	//Draw::Draw(, &src, &dst, color, 0.0f);
}